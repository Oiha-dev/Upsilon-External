#include <stdint.h>

#define MAP_WIDTH 32
#define MAP_DEPTH 32
#define MAP_HEIGHT 8

uint8_t MAP[MAP_WIDTH][MAP_DEPTH][MAP_HEIGHT];

/*
    0: air
    1: stone
    2: grass
    3: dirt
    4: cobblestone
    5: oak_planks
    6: bricks
    7: stone_bricks
    8: oak_log
    9: oak_leaves
    10: sand
    11: bookshelf
    12: tnt
    13: crafting_table
    14: furnace
    15: jukebox
    16: sponge
    17: gravel
    18: mossy_cobblestone
    19: coal_ore
    20: iron_ore
    21: bedrock
    22: iron_block
    23: gold_block
    24: diamond_block
 */

void initMap() {
    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
        for (uint8_t z = 0; z < MAP_DEPTH; z++) {
            for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
                if (y == 0) {
                    MAP[x][z][y] = 21;
                } else if (y == 1) {
                    MAP[x][z][y] = 1;
                } else if (y == 2) {
                    MAP[x][z][y] = 3;
                } else if (y == 3) {
                    MAP[x][z][y] = 2;
                } else {
                    MAP[x][z][y] = 0;
                }
            }
        }
    }
MAP[0][0][4] = 1;
MAP[0][2][4] = 2;
MAP[0][4][4] = 3;
MAP[0][6][4] = 4;
MAP[0][8][4] = 5;
MAP[0][10][4] = 6;
MAP[0][12][4] = 7;
MAP[0][14][4] = 8;
MAP[0][16][4] = 9;
MAP[0][18][4] = 10;
MAP[2][0][4] = 11;
MAP[4][0][4] = 12;
MAP[6][0][4] = 13;
MAP[8][0][4] = 14;
MAP[10][0][4] = 15;
MAP[12][0][4] = 16;
MAP[14][0][4] = 17;
MAP[16][0][4] = 18;
MAP[18][0][4] = 19;
MAP[20][0][4] = 20;
MAP[22][0][4] = 21;
MAP[0][20][4] = 22;
MAP[0][22][4] = 23;
MAP[3][3][4] = 24;
}