// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Sunny with a Chance of Asteroids Part 2

#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define INPUTS 1
#define MEMORY 4096
#define OUTPUTS 8

int main()
{
    Word inputs[INPUTS];
    Word memory[MEMORY];
    Word outputs[OUTPUTS];
    struct Emulator processor;
    clock_t start = clock();

    parser_parse(stdin, memory);
    emulator(&processor, memory);
    queue(&processor.inputs, inputs, INPUTS);
    queue(&processor.outputs, outputs, OUTPUTS);
    queue_enqueue(&processor.inputs, 5);
    emulator_execute(&processor);
    printf(
        "05b " WORD_FORMAT " %lf\n",
        processor.outputs.items[processor.outputs.last],
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
