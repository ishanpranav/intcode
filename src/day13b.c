// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Care Package Part 2

#include <math.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#include "day13.h"
#define INPUTS 1
#define MEMORY 8192
#define OUTPUTS 4096

int main(void)
{
    Word x;
    Word y;
    Word tile;
    Word ball = 0;
    Word paddle = 0;
    Word score = 0;
    Word memory[MEMORY];
    Word outputs[OUTPUTS];
    Word inputs[INPUTS];
    struct Emulator arcadeCabinet;

    parser_parse(stdin, memory);
    emulator(&arcadeCabinet, memory);
    queue(&arcadeCabinet.inputs, inputs, INPUTS);
    queue(&arcadeCabinet.outputs, outputs, OUTPUTS);

    memory[0] = 2;

    while (emulator_execute(&arcadeCabinet))
    {
        while (queue_try_dequeue(&arcadeCabinet.outputs, &x))
        {
            queue_try_dequeue(&arcadeCabinet.outputs, &y);
            queue_try_dequeue(&arcadeCabinet.outputs, &tile);

            if (x == -1 && !y)
            {
                score = tile;

                continue;
            }

            switch (tile)
            {
                case TILE_BALL: ball = x; break;
                case TILE_PADDLE: paddle = x; break;
            }
        }

        Word next = (ball > paddle) - (ball < paddle);

        queue_enqueue(&arcadeCabinet.inputs, next);
    }

    while (queue_try_dequeue(&arcadeCabinet.outputs, &x))
    {
        queue_try_dequeue(&arcadeCabinet.outputs, &y);
        queue_try_dequeue(&arcadeCabinet.outputs, &tile);

        if (x == -1 && !y)
        {
            score = tile;
        }
    }

    printf("13b " WORD_FORMAT "\n", score);

    return 0;
}
