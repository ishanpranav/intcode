#include <stdio.h>
#include "emulator.h"

enum Opcode
{
    OPCODE_ADD = 1,
    OPCODE_MULTIPLY = 2,
    OPCODE_INPUT = 3,
    OPCODE_OUTPUT = 4,
    OPCODE_TERMINATE = 99
};

typedef enum Opcode Opcode;

Word emulator_load(Emulator instance, Word* instruction, int slot)
{
    int denominator = 100;

    for (int i = 0; i < slot - 1; i++)
    {
        denominator *= 10;
    }

    Word value = instruction[slot];

    if ((*instruction / denominator) % 10 == 0)
    {
        return instance->memory[value];
    }

    return value;
}

void emulator_execute(Emulator instance)
{
    Word* instruction = instance->memory;

    for (;;)
    {
        Opcode opcode = *instruction % 100;

        switch (opcode)
        {
            case OPCODE_ADD:
            {
                Word a = emulator_load(instance, instruction, 1);
                Word b = emulator_load(instance, instruction, 2);
                Word* result = instance->memory + instruction[3];

                *result = a + b;
                instruction += 4;
            }
            break;

            case OPCODE_MULTIPLY:
            {
                Word a = emulator_load(instance, instruction, 1);
                Word b = emulator_load(instance, instruction, 2);
                Word* result = instance->memory + instruction[3];

                *result = a * b;
                instruction += 4;
            }
            break;

            case OPCODE_INPUT:
            {
                Word* result = instance->memory + instruction[1];

                *result = instance->input();
                instruction += 2;
            }
            break;

            case OPCODE_OUTPUT:
            {
                Word value = emulator_load(instance, instruction, 1);

                instance->ouput(value);
                instruction += 2;
            }
            break;

            case OPCODE_TERMINATE: return;
        }
    }
}
