#include <stdint.h>
#include <stddef.h>
#include "extapp_api.h"
#include "data/texture_data.h"
#include "world.c"

#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 31

int8_t cameraX = 5;
int8_t cameraY = 7;

typedef struct {
    uint8_t block;
    uint8_t face;
    uint8_t coord[3];
    uint8_t shadow;
} triangle;

triangle SCREEN[SCREEN_WIDTH][SCREEN_HEIGHT];
triangle SCREEN_OLD[SCREEN_WIDTH][SCREEN_HEIGHT];

uint8_t getDepth(triangle tri){
	return tri.coord[0] + tri.coord[1] + tri.coord[2];
}

uint16_t getColor(uint8_t colorIndex, uint8_t dark) {
    const uint8_t (*palette)[3] = dark ? COLOR_PALETTE_DARK : COLOR_PALETTE;
    return ((palette[colorIndex][0] >> 3) << 11) |
           ((palette[colorIndex][1] >> 2) << 5) |
           (palette[colorIndex][2] >> 3);
}

uint8_t needShadow(uint8_t x, uint8_t y, uint8_t z) {
    for (uint8_t step = 1; y + step < MAP_HEIGHT && z - step >= 0; step++) {
        if (MAP[x + step][z - step][y + step] != 0) {
            return 1;
        }
    }
    return 0;
}

void drawShadow(const uint8_t *texture, int16_t x, int16_t y, triangle tri) {
    for (int j = 0; j < ISO_HEIGHT; j++) {
        for (int i = 0; i < ISO_WIDTH; i++) {
            uint8_t colorIndexCut = TEXTURE_BLOCKMAP[j * ISO_WIDTH + i];
            if (colorIndexCut != tri.face) continue;

            if (!texture) {
                extapp_pushRectUniform(x + i, y + j, 1, 1, 0x555F);
                continue;
            }

            uint8_t colorIndex = texture[j * ISO_WIDTH + i];
            if (colorIndex != 255) {
            	extapp_pushRectUniform(x + i, y + j, 1, 1, getColor(colorIndex, 1));
            }
        }
    }
}

void drawSpriteCut(const uint8_t *texture, int16_t x, int16_t y, triangle tri) {
    static const int8_t cutOffsets[7][2] = {
        {0, 0}, {0, 0}, {-16, 0}, {-16, -8}, {-16, -16}, {0, -16}, {0, -8}
    };

    x += cutOffsets[tri.face][0];
    y += cutOffsets[tri.face][1];

    if (tri.shadow != 0) {
      	drawShadow(texture, x, y, tri);
    	return;
    }
    for (int j = 0; j < ISO_HEIGHT; j++) {
        for (int i = 0; i < ISO_WIDTH; i++) {
            uint8_t colorIndexCut = TEXTURE_BLOCKMAP[j * ISO_WIDTH + i];
            if (colorIndexCut != tri.face) continue;

            if (!texture) {
                extapp_pushRectUniform(x + i, y + j, 1, 1, 0x555F);
                continue;
            }

            uint8_t colorIndex = texture[j * ISO_WIDTH + i];
            if (colorIndex != 255) {
            	extapp_pushRectUniform(x + i, y + j, 1, 1, getColor(colorIndex, 0));
            }
        }
    }
}

void setBlockFace(uint8_t x, uint8_t y, uint8_t block, uint8_t face, uint8_t coord[3], bool shadow) {
    SCREEN[x][y] = (triangle){block, face, {coord[0], coord[1], coord[2]}, shadow};
}

void addBlock(uint8_t x, uint8_t y, uint8_t block, uint8_t coord[3], bool shadow) {
    if (x + 1 >= SCREEN_WIDTH || y + 2 >= SCREEN_HEIGHT) return;
    setBlockFace(x, y, block, 1, coord, shadow);
    setBlockFace(x + 1, y, block, 2, coord, shadow);
    setBlockFace(x + 1, y + 1, block, 3, coord, shadow);
    setBlockFace(x + 1, y + 2, block, 4, coord, shadow);
    setBlockFace(x, y + 2, block, 5, coord, shadow);
    setBlockFace(x, y + 1, block, 6, coord, shadow);
}

bool triangleEquals(triangle a, triangle b) {
    return a.block == b.block &&
           a.face == b.face &&
           a.coord[0] == b.coord[0] &&
           a.coord[1] == b.coord[1] &&
           a.coord[2] == b.coord[2] &&
           a.shadow == b.shadow;
}

void initScreen() {
    for (uint8_t x = 0; x < 9; x++) {
        for (uint8_t y = 0; y < 14; y++) {
            addBlock(x * 2 + 1, y * 2 + 1, 0, 0, (uint8_t[3]){0, 0, 0});
        }
    }
}

void initScreenOld() {
    for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
        for (uint8_t y = 0; y < SCREEN_HEIGHT; y++) {
            SCREEN_OLD[x][y] = SCREEN[x][y];
        }
    }
}

void drawScreen() {
    for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
        for (uint8_t y = 0; y < SCREEN_HEIGHT; y++) {
            uint8_t block = SCREEN[x][y].block;
            if (triangleEquals(SCREEN[x][y], SCREEN_OLD[x][y])) {
                continue;
            }
            if (block != 0) {
            	drawSpriteCut(TEXTURES[block - 1], x * 16, y * 8 - 8, SCREEN[x][y]);
            } else {
                drawSpriteCut(0, x * 16, y * 8 - 8, SCREEN[x][y]);
            }
            SCREEN_OLD[x][y] = SCREEN[x][y];
        }
    }
}

void mapToScreen() {
    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
        for (uint8_t z = 0; z < MAP_DEPTH; z++) {
            for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
                uint8_t block = MAP[x][z][y];
                if (block == 0) continue;

                int16_t screen_x = x * -1 + z + cameraX * 2;
                int16_t screen_y = x + z + cameraY * 2 - y * 2;

                if (screen_x >= 0 && screen_x + 1 < SCREEN_WIDTH &&
                    screen_y >= 0 && screen_y + 1 < SCREEN_HEIGHT) {
                    addBlock(screen_x, screen_y, block, (uint8_t[3]){x, y, z}, needShadow(x, y, z));
                }
            }
        }
    }
}

void clearScreen() {
    extapp_pushRectUniform(0, 0, 320, 240, 0x555F);
}
