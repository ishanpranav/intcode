// Licensed under the MIT license.

// Sunny with a Chance of Asteroids Part 1

#include <stdio.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 100000

int main(int count, ZString args[])
{
    if (count < 2)
    {
        printf("Usage: day05a <program>\n");

        return 1;
    }

    Word memory[MEMORY];
    struct Emulator emulator =
    {
        .input = stdin,
        .output = stdout,
        .memory = memory
    };
    clock_t start = clock();

    if (!parser_parse_file(args[1], memory))
    {
        fprintf(stderr, "Error: I/O.\n");

        return 1;
    }

    emulator_execute(&emulator);
    printf("05a %lf", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
