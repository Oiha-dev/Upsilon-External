#include <stdint.h>
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
} triangle;

triangle SCREEN[SCREEN_WIDTH][SCREEN_HEIGHT];

triangle SCREEN_OLD[SCREEN_WIDTH][SCREEN_HEIGHT];

void drawSpriteCut(const uint8_t *texture, int16_t x, int16_t y, uint8_t cut) {
    if (cut == 2) {
        x -= 16;
    } else if (cut == 3) {
        x -= 16;
        y -= 8;
    } else if (cut == 4) {
        x -= 16;
        y -= 16;
    } else if (cut == 5) {
        y -= 16;
    } else if (cut == 6) {
        y -= 8;
    }
    for (int j = 0; j < ISO_HEIGHT; j++) {
        for (int i = 0; i < ISO_WIDTH; i++) {

			uint8_t colorIndexCut = TEXTURE_BLOCKMAP[j * ISO_WIDTH + i];

            if (texture == 0) {
              	if (colorIndexCut == cut) {
                    extapp_pushRectUniform(x + i, y + j, 1, 1, 0x555F);
                  }
                continue;
            }

            uint8_t colorIndex = texture[j * ISO_WIDTH + i];
            if (colorIndex != 255 && colorIndexCut == cut) {
                uint16_t color = ((COLOR_PALETTE[colorIndex][0] >> 3) << 11) |
                                ((COLOR_PALETTE[colorIndex][1] >> 2) << 5) |
                                (COLOR_PALETTE[colorIndex][2] >> 3);

                extapp_pushRectUniform(x + i, y + j, 1, 1, color);
            }
        }
    }
}

void addBlock(uint8_t x, uint8_t y, uint8_t block) {
    if (x + 1 >= SCREEN_WIDTH || y + 2 >= SCREEN_HEIGHT) {
        return;
    }

    SCREEN[x][y].block = block;
    SCREEN[x][y].face = 1;
    SCREEN[x+1][y].block = block;
    SCREEN[x+1][y].face = 2;
    SCREEN[x+1][y+1].block = block;
    SCREEN[x+1][y+1].face = 3;
    SCREEN[x+1][y+2].block = block;
    SCREEN[x+1][y+2].face = 4;
    SCREEN[x][y+2].block = block;
    SCREEN[x][y+2].face = 5;
    SCREEN[x][y+1].block = block;
    SCREEN[x][y+1].face = 6;
}

void initScreen() {
    for (uint8_t x = 0; x < 9; x++) {
        for (uint8_t y = 0; y < 14; y++) {
            addBlock(x*2+1, y*2+1, 0);
        }
    }
}

void drawScreen() {
    for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
        for (uint8_t y = 0; y < SCREEN_HEIGHT; y++) {
            uint8_t block = SCREEN[x][y].block;
            uint8_t face = SCREEN[x][y].face;
            if (SCREEN_OLD[x][y].block == block && SCREEN_OLD[x][y].face == face) {
                continue;
            }
            if (block != 0) {
            	drawSpriteCut(TEXTURES[block - 1], x * 16, y * 8 - 8, face);
            } else {
                drawSpriteCut(0, x * 16, y * 8 - 8, face);
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
                if (block != 0) {
                    int16_t screen_x = x * -1 + z + cameraX*2;
                    int16_t screen_y = x + z + cameraY*2 - y*2;

                    if (screen_x >= 0 && screen_x + 1 < SCREEN_WIDTH &&
                        screen_y >= 0 && screen_y + 1 < SCREEN_HEIGHT) {
                        addBlock(screen_x, screen_y, block);
                    }
                }
            }
        }
    }
}

void clearScreen() {
    extapp_pushRectUniform (0, 0, 320, 240, 0x555F);
}