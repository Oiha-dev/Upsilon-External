#include <stdint.h>

#define MAP_WIDTH 32
#define MAP_DEPTH 32
#define MAP_HEIGHT 10

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
    MAP[2][0][4] = 7;
MAP[3][0][4] = 7;
MAP[4][0][4] = 7;
MAP[2][0][5] = 7;
MAP[2][0][6] = 7;
MAP[3][0][5] = 7;
MAP[3][0][6] = 7;
MAP[4][0][5] = 7;
MAP[4][0][6] = 7;
MAP[6][2][4] = 7;
MAP[6][2][5] = 7;
MAP[6][2][6] = 7;
MAP[6][3][6] = 7;
MAP[6][4][4] = 7;
MAP[6][4][5] = 7;
MAP[6][4][6] = 7;
MAP[4][6][4] = 7;
MAP[4][6][5] = 7;
MAP[4][6][6] = 7;
MAP[3][6][4] = 7;
MAP[3][6][5] = 7;
MAP[3][6][6] = 7;
MAP[2][6][4] = 7;
MAP[2][6][5] = 7;
MAP[2][6][6] = 7;
MAP[0][3][4] = 7;
MAP[0][2][4] = 7;
MAP[0][2][5] = 7;
MAP[0][2][6] = 7;
MAP[0][3][5] = 7;
MAP[0][3][6] = 7;
MAP[0][4][4] = 7;
MAP[0][4][5] = 7;
MAP[0][4][6] = 7;
MAP[0][5][4] = 8;
MAP[0][5][5] = 8;
MAP[1][6][4] = 8;
MAP[1][6][5] = 8;
MAP[1][6][6] = 8;
MAP[5][6][4] = 8;
MAP[5][6][5] = 8;
MAP[5][6][6] = 8;
MAP[6][5][4] = 8;
MAP[6][5][5] = 8;
MAP[6][5][6] = 8;
MAP[6][1][4] = 8;
MAP[6][1][5] = 8;
MAP[6][1][6] = 8;
MAP[5][0][4] = 8;
MAP[5][0][5] = 8;
MAP[5][0][6] = 8;
MAP[1][0][4] = 8;
MAP[1][0][5] = 8;
MAP[1][0][6] = 8;
MAP[0][1][4] = 8;
MAP[0][1][5] = 8;
MAP[0][1][6] = 8;
MAP[0][5][6] = 8;
}