// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Sunny with a Chance of Asteroids Part 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 4096

Word result;

static Word emulator_on_input()
{
    return 5;
}

static void emulator_on_output(Word value)
{
    result = value;
}

int main()
{
    Word memory[MEMORY];
    struct Emulator emulator =
    {
        .memory = memory,
        .input = emulator_on_input,
        .ouput = emulator_on_output
    };
    clock_t start = clock();

    parser_parse(stdin, memory);
    emulator_execute(&emulator);
    printf(
        "05b " WORD_FORMAT " %lf\n",
        result,
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
