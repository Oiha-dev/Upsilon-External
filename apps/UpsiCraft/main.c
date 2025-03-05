#include <stddef.h>
#include <stdint.h>
#include "screen.c"

void updateScreen() {
    initScreen();
    mapToScreen();
    drawScreen();
}

void handleInput() {
    int dx = 0, dy = 0;
    if (extapp_isKeydown(3)) dx++;
    if (extapp_isKeydown(0)) dx--;
    if (extapp_isKeydown(2)) dy++;
    if (extapp_isKeydown(1)) dy--;

    cameraX += dx;
    cameraY += dy;
}


void extapp_main() {
    clearScreen();
    initScreen();
    initScreenOld();
    initMap();
    mapToScreen();
    drawScreen();

    while (!extapp_isKeydown(5)) {
        handleInput();
        updateScreen();
        extapp_msleep(100);
    }
}