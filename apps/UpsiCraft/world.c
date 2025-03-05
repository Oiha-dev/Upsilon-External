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
MAP[14][14][4] = 4;
MAP[13][15][4] = 4;
MAP[15][13][4] = 4;
MAP[15][15][4] = 4;
MAP[16][14][4] = 4;
MAP[14][16][4] = 4;
MAP[16][16][4] = 4;
MAP[15][17][4] = 4;
MAP[17][17][4] = 4;
MAP[17][15][4] = 4;
MAP[18][14][4] = 4;
MAP[18][16][4] = 4;
MAP[18][18][4] = 4;
MAP[14][18][4] = 4;
MAP[16][18][4] = 4;
MAP[17][14][4] = 7;
MAP[16][15][4] = 7;
MAP[15][16][4] = 7;
MAP[14][17][4] = 7;
MAP[14][15][4] = 7;
MAP[15][14][4] = 7;
MAP[17][16][4] = 7;
MAP[16][17][4] = 7;
MAP[17][18][4] = 7;
MAP[18][17][4] = 7;
MAP[18][15][4] = 7;
MAP[17][13][4] = 4;
MAP[16][13][4] = 7;
MAP[14][13][4] = 7;
MAP[13][14][4] = 7;
MAP[13][16][4] = 7;
MAP[15][18][4] = 7;
MAP[18][13][4] = 8;
MAP[18][13][5] = 8;
MAP[18][13][6] = 8;
MAP[18][13][7] = 8;
MAP[13][18][4] = 8;
MAP[13][18][5] = 8;
MAP[13][18][6] = 8;
MAP[13][18][7] = 8;
MAP[13][13][4] = 8;
MAP[13][13][5] = 8;
MAP[13][13][6] = 8;
MAP[13][13][7] = 8;
MAP[13][17][4] = 11;
MAP[13][17][5] = 11;
MAP[13][17][6] = 11;
MAP[13][17][7] = 11;
MAP[13][16][5] = 11;
MAP[13][15][5] = 11;
MAP[13][16][6] = 11;
MAP[13][16][7] = 11;
MAP[13][15][6] = 11;
MAP[13][15][7] = 11;
MAP[13][14][5] = 11;
MAP[13][14][6] = 11;
MAP[13][14][7] = 11;
MAP[14][13][5] = 11;
MAP[15][13][5] = 11;
MAP[16][13][5] = 11;
MAP[17][13][5] = 11;
MAP[14][13][6] = 11;
MAP[15][13][6] = 11;
MAP[16][13][6] = 11;
MAP[17][13][6] = 11;
MAP[14][13][7] = 11;
MAP[15][13][7] = 11;
MAP[16][13][7] = 11;
MAP[17][13][7] = 11;
MAP[17][14][5] = 15;
MAP[14][16][5] = 14;
}