#include <stddef.h>
#include <stdint.h>
#include "screen.c"
#include "world.c"

void extapp_main(void) {
    /*for (uint8_t i = 0; i < TEXTURE_COUNT; i++) {
        uint16_t x = 10 + (i % 6) * 50;
        uint16_t y = 10 + (i / 6) * 50;
        drawSpriteCut(TEXTURES[i], x, y, 5);
    }*/

    initScreen();
    drawScreen();


    while (!extapp_isKeydown(5)) {
        extapp_msleep(100);
    }
}