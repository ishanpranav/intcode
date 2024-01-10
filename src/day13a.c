// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Care Package Part 1

#include <stdlib.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 8192
#define OUTPUTS 4096

enum Tile
{
    TILE_EMPTY = 0,
    TILE_WALL = 1,
    TILE_BLOCK = 2,
    TILE_HORIZONTAL_PADDLE = 3,
    TILE_BALL = 4
};

typedef enum Tile Tile;

int main(void)
{
    int total = 0;
    Word memory[MEMORY];
    Word outputs[OUTPUTS];
    struct Emulator arcadeCabinet;

    parser_parse(stdin, memory);
    emulator(&arcadeCabinet, memory);
    queue(&arcadeCabinet.outputs, outputs, OUTPUTS);
    emulator_execute(&arcadeCabinet);

    Word tile;

    while (queue_try_dequeue(&arcadeCabinet.outputs, &tile))
    {
        queue_try_dequeue(&arcadeCabinet.outputs, &tile);
        queue_try_dequeue(&arcadeCabinet.outputs, &tile);

        if (tile == TILE_BLOCK)
        {
            total++;
        }
    }

    printf("13a %d\n", total);

    return 0;
}
