// Licensed under the MIT license.

// Sunny with a Chance of Asteroids Part 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 100000

Word result;

static Word emulator_on_input()
{
    return 1;
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
        "05a " WORD_FORMAT " %lf\n",
        result,
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
