#include <stdint.h>
#include "extapp_api.h"
#include "data/texture_data.h"

#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 31

typedef struct {
    uint8_t block;
    uint8_t face;
} triangle;

triangle SCREEN[SCREEN_WIDTH][SCREEN_HEIGHT];

void drawSpriteCut(const uint8_t *texture, int16_t x, int16_t y, uint8_t cut) {
    if (cut == 2) {
        x -= 16;
    } else if (cut == 3) {
        x -= 16;
        y -= 7;
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
            uint8_t colorIndex = texture[j * ISO_WIDTH + i];
            uint8_t colorIndexCut = TEXTURE_BLOCKMAP[j * ISO_WIDTH + i];

            if (colorIndex != 255 && colorIndexCut == cut) {
                uint16_t color = ((COLOR_PALETTE[colorIndex][0] >> 3) << 11) |
                                ((COLOR_PALETTE[colorIndex][1] >> 2) << 5) |
                                (COLOR_PALETTE[colorIndex][2] >> 3);

                extapp_pushRectUniform(x + i, y + j, 1, 1, color);
            }
        }
    }
}

void initScreen() {
    for (uint8_t x = 0; x < 20; x++) {
        for (uint8_t y = 0; y < 31; y++) {
            SCREEN[x][y].block = 1;
            SCREEN[x][y].face = 1;
            if ( x % 2 ) {
                SCREEN[x][y].face = 2;
            }
            if ( y % 2 ) {
                SCREEN[x][y].block = 13;
                if ( x % 2 ) {
                    SCREEN[x][y].face = 1;
                } else {
                    SCREEN[x][y].face = 2;
                }
            }
        }
    }
}

void drawScreen() {
    for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
        for (uint8_t y = 0; y < SCREEN_HEIGHT; y++) {
            uint8_t block = SCREEN[x][y].block;
            uint8_t face = SCREEN[x][y].face;

            if (block != 0) {
                drawSpriteCut(TEXTURES[block - 1], x * 16, y * 8 - 8, face);
            }
        }
    }
}