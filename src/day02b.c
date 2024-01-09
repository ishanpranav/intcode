// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// 1202 Program Alarm Part 2

#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 256

static Word scan(Word image[], int imageSize)
{
    Word memory[MEMORY];
    struct Emulator processor;
    
    emulator(&processor, memory);

    for (Word noun = 0; noun < 100; noun++)
    {
        for (Word verb = 0; verb < 100; verb++)
        {
            emulator_reimage(&processor, image, imageSize);

            memory[1] = noun;
            memory[2] = verb;

            emulator_execute(&processor);

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
    Word image[MEMORY];
    Word product = scan(image, parser_parse(stdin, image));

    printf("02b " WORD_FORMAT "\n", product);

    return 0;
}
