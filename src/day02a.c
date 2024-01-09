// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// 1202 Program Alarm Part 1

#include "../lib/emulator.h"
#include "../lib/parser.h"
#define MEMORY 256

int main(void)
{
    Word memory[MEMORY];
    struct Emulator processor;

    parser_parse(stdin, memory);
    
    memory[1] = 12;
    memory[2] = 2;

    emulator(&processor, memory);
    emulator_execute(&processor);
    printf("02a " WORD_FORMAT "\n", memory[0]);

    return 0;
}
