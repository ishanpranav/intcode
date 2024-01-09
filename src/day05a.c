// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Sunny with a Chance of Asteroids Part 1

#include <stdlib.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 100000

int main()
{
    Word memory[MEMORY];
    struct Emulator processor;
    clock_t start = clock();

    parser_parse(stdin, memory);
    emulator(&processor, memory);
    emulator_input(&processor, 1);
    emulator_execute(&processor);
    printf(
        "05a " WORD_FORMAT " %lf\n",
        processor.outputs[processor.outputCount - 1],
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
