// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Care Package Part 1

#include "../lib/emulator.h"
#include "../lib/parser.h"
#include "day13.h"
#define MEMORY 8192
#define OUTPUTS 4096

int main(void)
{
    Word tile;
    int total = 0;
    Word memory[MEMORY];
    Word outputs[OUTPUTS];
    struct Emulator arcadeCabinet;

    parser_parse(stdin, memory);
    emulator(&arcadeCabinet, memory);
    queue(&arcadeCabinet.outputs, outputs, OUTPUTS);
    emulator_execute(&arcadeCabinet);

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
