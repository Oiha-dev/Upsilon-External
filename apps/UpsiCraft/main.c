#include <stddef.h>
#include <stdint.h>
#include "extapp_api.h"
#include "render.c"
#include "world_transform.c"

void extapp_main(void) {
    for (uint8_t i = 0; i < TEXTURE_COUNT; i++) {
        uint16_t x = 10 + (i % 6) * 50;
        uint16_t y = 10 + (i / 6) * 50;
        drawSpriteCut(TEXTURES[i], x, y, 1);
        drawSpriteCut(TEXTURES[i], x, y, 2);
        drawSpriteCut(TEXTURES[i], x, y, 3);
    }

    while (!extapp_isKeydown(5)) {
        extapp_msleep(100);
    }
}