// Licensed under the MIT license.

// 1202 Program Alarm Part 2

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 256

static Word scan(Word clean[], int length)
{
    for (Word noun = 0; noun < 100; noun++)
    {
        for (Word verb = 0; verb < 100; verb++)
        {
            Word dirty[MEMORY];

            memcpy(dirty, clean, sizeof(Word) * length);

            dirty[1] = noun;
            dirty[2] = verb;

            emulator_execute(dirty);

            if (dirty[0] == 19690720)
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
    struct Emulator emulator =
    {
        .memory = memory
    };
    clock_t start = clock();
    Word product = scan(memory, parser_parse(stdin, memory));

    printf(
        "02b " WORD_FORMAT " %lf\n",
        product,
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
