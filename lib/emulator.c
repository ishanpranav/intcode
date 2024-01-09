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

static bool emulator_on_input(Emulator instance, Word* result)
{
    return queue_try_dequeue(&instance->inputs, result);
}

static void emulator_on_output(Emulator instance, Word word)
{
    queue_enqueue(&instance->outputs, word);
}

void emulator(Emulator instance, Word memory[])
{
    instance->memory = memory;
    instance->input = emulator_on_input;
    instance->output = emulator_on_output;
    
    queue(&instance->inputs, NULL, 0);
    queue(&instance->outputs, NULL, 0);
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
                Word input;
                
                instance->input(instance, &input);
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

void queue(Queue instance, Word buffer[], int capacity)
{
    instance->items = buffer;
    instance->first = -1;
    instance->last = -1;
    instance->capacity = capacity;
}

void queue_enqueue(Queue instance, Word item)
{
    if (instance->first == -1)
    {
        instance->first = 0;
        instance->last = 0;
    }
    else if (instance->first && instance->last == instance->capacity - 1)
    {
        instance->last = 0;
    }
    else
    {
        instance->last++;
    }

    instance->items[instance->last] = item;
}

bool queue_try_dequeue(Queue instance, Word* result)
{
    if (instance->first == -1)
    {
        return false;
    }

    *result = instance->items[instance->first];

    if (instance->first == instance->last)
    {
        instance->first = -1;
        instance->last = -1;
    }
    else if (instance->first == instance->capacity - 1)
    {
        instance->first = 0;
    }
    else
    {
        instance->first++;
    }

    return true;
}
