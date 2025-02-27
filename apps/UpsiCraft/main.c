#include <stddef.h>
#include <stdint.h>
#include "extapp_api.h"
#include "drawing.c"

void extapp_main(void) {
    for (uint8_t i = 0; i < TEXTURE_COUNT; i++) {
        uint16_t x = 10 + (i % 6) * 50;
        uint16_t y = 10 + (i / 6) * 50;
        drawSpriteCut(TEXTURES[i], x, y, 1);
        drawSpriteCut(TEXTURES[i], x, y, 2);
        drawSpriteCut(TEXTURES[i], x, y, 3);
        drawSpriteCut(TEXTURES[i], x, y, 4);
        drawSpriteCut(TEXTURES[i], x, y, 5);
    }

    while (!extapp_isKeydown(5)) {
        extapp_msleep(100);
    }
}