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
    uint8_t depth;
    uint8_t coord[3];
} triangle;

triangle SCREEN[SCREEN_WIDTH][SCREEN_HEIGHT];
triangle SCREEN_OLD[SCREEN_WIDTH][SCREEN_HEIGHT];

uint16_t getColor(uint8_t colorIndex, uint8_t dark) {
    const uint8_t (*palette)[3] = dark ? COLOR_PALETTE_DARK : COLOR_PALETTE;
    return ((palette[colorIndex][0] >> 3) << 11) |
           ((palette[colorIndex][1] >> 2) << 5) |
           (palette[colorIndex][2] >> 3);
}

bool needShawod(uint8_t x, uint8_t y, uint8_t z) {
    if (MAP[x][z - 1][y + 1] != 0){
    	return true;
    }
    return false;
}




void drawSpriteCut(const uint8_t *texture, int16_t x, int16_t y, uint8_t cut, uint8_t depth, uint8_t coord[3]) {
    static const int8_t cutOffsets[7][2] = {
        {0, 0}, {0, 0}, {-16, 0}, {-16, -8}, {-16, -16}, {0, -16}, {0, -8}
    };

    x += cutOffsets[cut][0];
    y += cutOffsets[cut][1];

    for (int j = 0; j < ISO_HEIGHT; j++) {
        for (int i = 0; i < ISO_WIDTH; i++) {
            uint8_t colorIndexCut = TEXTURE_BLOCKMAP[j * ISO_WIDTH + i];
            if (colorIndexCut != cut) continue;

            if (!texture) {
                extapp_pushRectUniform(x + i, y + j, 1, 1, 0x555F);
                continue;
            }

            uint8_t colorIndex = texture[j * ISO_WIDTH + i];
            if (colorIndex != 255) {
                extapp_pushRectUniform(x + i, y + j, 1, 1, getColor(colorIndex, cut == 3 || cut == 4 || ((cut == 1 || cut == 2) && needShawod(coord[0], coord[1], coord[2]))));
            }
        }
    }
}

void setBlockFace(uint8_t x, uint8_t y, uint8_t block, uint8_t face, uint8_t depth, uint8_t coord[3]) {
    SCREEN[x][y] = (triangle){block, face, depth, {coord[0], coord[1], coord[2]}};
}

void addBlock(uint8_t x, uint8_t y, uint8_t block, uint8_t depth, uint8_t coord[3]) {
    if (x + 1 >= SCREEN_WIDTH || y + 2 >= SCREEN_HEIGHT) return;
    setBlockFace(x, y, block, 1, depth, coord);
    setBlockFace(x + 1, y, block, 2, depth, coord);
    setBlockFace(x + 1, y + 1, block, 3, depth, coord);
    setBlockFace(x + 1, y + 2, block, 4, depth, coord);
    setBlockFace(x, y + 2, block, 5, depth, coord);
    setBlockFace(x, y + 1, block, 6, depth, coord);
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
            uint8_t face = SCREEN[x][y].face;
            uint8_t depth = SCREEN[x][y].depth;
            if (SCREEN_OLD[x][y].block == block && SCREEN_OLD[x][y].face == face && SCREEN_OLD[x][y].depth == depth) {
                continue;
            }
            if (block != 0) {
            	drawSpriteCut(TEXTURES[block - 1], x * 16, y * 8 - 8, face, depth, SCREEN[x][y].coord);
            } else {
                drawSpriteCut(0, x * 16, y * 8 - 8, face, depth, SCREEN[x][y].coord);
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
                    addBlock(screen_x, screen_y, block, x + z + y, (uint8_t[3]){x, y, z});
                }
            }
        }
    }
}

void clearScreen() {
    extapp_pushRectUniform(0, 0, 320, 240, 0x555F);
}
