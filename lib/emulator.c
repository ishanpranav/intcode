// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdio.h>
#include "emulator.h"

enum Opcode
{
    OPCODE_ADD = 1,
    OPCODE_MULTIPLY = 2,
    OPCODE_INPUT = 3,
    OPCODE_OUTPUT = 4,
    OPCODE_JUMP_IF_TRUE = 5,
    OPCODE_JUMP_IF_FALSE = 6,
    OPCODE_LESS_THAN = 7,
    OPCODE_EQUALS = 8,
    OPCODE_TERMINATE = 99
};

typedef enum Opcode Opcode;

static Word emulator_on_input(Emulator instance)
{
    if (instance->firstInput == -1)
    {
        return 0;
    }

    Word result = instance->inputs[instance->firstInput];

    if (instance->firstInput == instance->lastInput)
    {
        instance->firstInput = -1;
        instance->lastInput = -1;
    }
    else if (instance->firstInput == EMULATOR_INPUTS_CAPACITY - 1)
    {
        instance->firstInput = 0;
    }
    else
    {
        instance->firstInput++;
    }

    return result;
}

static void emulator_on_output(Emulator instance, Word word)
{
    instance->outputs[instance->outputCount] = word;
    instance->outputCount++;
}

void emulator(Emulator instance, Word memory[])
{
    instance->memory = memory;
    instance->input = emulator_on_input;
    instance->output = emulator_on_output;
    instance->firstInput = -1;
    instance->firstInput = -1;
    instance->outputCount = 0;
}

static void emulator_move(
    Emulator instance, 
    Word* instruction, 
    Word result, 
    int slot)
{
    instance->memory[instruction[slot]] = result;
}

static Word emulator_load(Emulator instance, Word* instruction, int slot)
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

void emulator_input(Emulator instance, Word value)
{
    if (instance->firstInput == -1)
    {
        instance->firstInput = 0;
        instance->lastInput = 0;
    }
    else if (instance->firstInput && 
        instance->lastInput == EMULATOR_INPUTS_CAPACITY - 1)
    {
        instance->lastInput = 0;
    }
    else
    {
        instance->lastInput++;
    }

    instance->inputs[instance->lastInput] = value;
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

                emulator_move(instance, instruction, a + b, 3);

                instruction += 4;
            }
            break;

            case OPCODE_MULTIPLY:
            {
                Word a = emulator_load(instance, instruction, 1);
                Word b = emulator_load(instance, instruction, 2);

                emulator_move(instance, instruction, a * b, 3);

                instruction += 4;
            }
            break;

            case OPCODE_INPUT:
            {
                Word input = instance->input(instance);

                emulator_move(instance, instruction, input, 1);

                instruction += 2;
            }
            break;

            case OPCODE_OUTPUT:
            {
                Word output = emulator_load(instance, instruction, 1);

                instance->output(instance, output);
                instruction += 2;
            }
            break;

            case OPCODE_JUMP_IF_TRUE:
                if (emulator_load(instance, instruction, 1))
                {
                    Word label = emulator_load(instance, instruction, 2);

                    instruction = instance->memory + label;

                    break;
                }

                instruction += 3;
                break;

            case OPCODE_JUMP_IF_FALSE:
                if (!emulator_load(instance, instruction, 1))
                {
                    Word label = emulator_load(instance, instruction, 2);

                    instruction = instance->memory + label;

                    break;
                }

                instruction += 3;
                break;

            case OPCODE_LESS_THAN:
            {
                Word a = emulator_load(instance, instruction, 1);
                Word b = emulator_load(instance, instruction, 2);

                emulator_move(instance, instruction, a < b, 3);

                instruction += 4;
            }
            break;

            case OPCODE_EQUALS:
            {
                Word a = emulator_load(instance, instruction, 1);
                Word b = emulator_load(instance, instruction, 2);

                emulator_move(instance, instruction, a == b, 3);

                instruction += 4;
            }
            break;

            case OPCODE_TERMINATE: return;
        }
    }
}
