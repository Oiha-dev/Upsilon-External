#include <stddef.h>
#include <stdint.h>
#include "screen.c"

void extapp_main(void) {
    clearScreen();
    initScreen();
    initMap();
    mapToScreen();
    drawScreen();

    while (!extapp_isKeydown(5)) {
        if (extapp_isKeydown(3)) {
            cameraX++;
            clearScreen();
            initScreen();
            mapToScreen();
            drawScreen();
        }
        if (extapp_isKeydown(0)) {
            cameraX--;
            clearScreen();
            initScreen();
            mapToScreen();
            drawScreen();
        }
        if (extapp_isKeydown(2)) {
            cameraY++;
            clearScreen();
            initScreen();
            mapToScreen();
            drawScreen();
        }
        if (extapp_isKeydown(1)) {
            cameraY--;
            clearScreen();
            initScreen();
            mapToScreen();
            drawScreen();
        }
        extapp_msleep(100);
    }
}