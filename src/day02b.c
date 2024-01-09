// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// 1202 Program Alarm Part 2

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 256

static Word scan(Word image[], int length)
{
    for (Word noun = 0; noun < 100; noun++)
    {
        for (Word verb = 0; verb < 100; verb++)
        {
            Word memory[MEMORY];
            struct Emulator emulator =
            {
                .memory = memory
            };

            memcpy(memory, image, sizeof(Word) * length);

            memory[1] = noun;
            memory[2] = verb;

            emulator_execute(&emulator);

            if (memory[0] == 19690720)
            {
                return noun * 100 + verb;
            }
        }
    }

    return 0;
}

int main(void)
{
    Word memory[MEMORY];
    clock_t start = clock();
    Word product = scan(memory, parser_parse(stdin, memory));

    printf(
        "02b " WORD_FORMAT " %lf\n",
        product,
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
