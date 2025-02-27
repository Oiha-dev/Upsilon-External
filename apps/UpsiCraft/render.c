#include <stddef.h>
#include <stdint.h>
#include "extapp_api.h"
#include "data/texture_data.h"

void drawSpriteCut(const uint8_t *texture, int16_t x, int16_t y, uint8_t cut) {
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