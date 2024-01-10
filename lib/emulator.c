// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdio.h>
#include <string.h>
#include "emulator.h"

enum Mode
{
    MODE_REFERENCE = 0,
    MODE_VALUE = 1,
    MODE_OFFSET = 2
};

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
    OPCODE_OFFSET = 9,
    OPCODE_TERMINATE = 99
};

enum Slot
{
    SLOT_FIRST = 100,
    SLOT_SECOND = 1000,
    SLOT_THIRD = 10000
};

typedef enum Opcode Opcode;
typedef enum Slot Slot;

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
    instance->instruction = instance->memory;
    instance->offset = 0;
    instance->input = emulator_on_input;
    instance->output = emulator_on_output;

    queue(&instance->inputs, NULL, 0);
    queue(&instance->outputs, NULL, 0);
}

static Word* emulator_address(Emulator instance, int index, Slot slot)
{
    Word value = instance->instruction[index];

    switch ((*instance->instruction / slot) % 10)
    {
        case MODE_REFERENCE: return instance->memory + value;

        case MODE_VALUE:
            instance->scratchRegister = value;

            return &instance->scratchRegister;

        case MODE_OFFSET: return instance->memory + instance->offset + value;
    }

    return NULL;
}

bool emulator_execute(Emulator instance)
{
    for (;;)
    {
        Opcode opcode = *instance->instruction % 100;

        switch (opcode)
        {
            case OPCODE_ADD:
            {
                Word a = *emulator_address(instance, 1, SLOT_FIRST);
                Word b = *emulator_address(instance, 2, SLOT_SECOND);

                *emulator_address(instance, 3, SLOT_THIRD) = a + b;

                instance->instruction += 4;
            }
            break;

            case OPCODE_MULTIPLY:
            {
                Word a = *emulator_address(instance, 1, SLOT_FIRST);
                Word b = *emulator_address(instance, 2, SLOT_SECOND);

                *emulator_address(instance, 3, SLOT_THIRD) = a * b;

                instance->instruction += 4;
            }
            break;

            case OPCODE_INPUT:
            {
                Word input;

                if (!instance->input(instance, &input))
                {
                    return true;
                }

                *emulator_address(instance, 1, SLOT_FIRST) = input;

                instance->instruction += 2;
            }
            break;

            case OPCODE_OUTPUT:
            {
                Word output = *emulator_address(instance, 1, SLOT_FIRST);

                instance->output(instance, output);
                instance->instruction += 2;
            }
            break;

            case OPCODE_JUMP_IF_TRUE:
                if (*emulator_address(instance, 1, SLOT_FIRST))
                {
                    Word label = *emulator_address(instance, 2, SLOT_SECOND);

                    instance->instruction = instance->memory + label;

                    break;
                }

                instance->instruction += 3;
                break;

            case OPCODE_JUMP_IF_FALSE:
                if (!*emulator_address(instance, 1, SLOT_FIRST))
                {
                    Word label = *emulator_address(instance, 2, SLOT_SECOND);

                    instance->instruction = instance->memory + label;

                    break;
                }

                instance->instruction += 3;
                break;

            case OPCODE_LESS_THAN:
            {
                Word left = *emulator_address(instance, 1, SLOT_FIRST);
                Word right = *emulator_address(instance, 2, SLOT_SECOND);

                *emulator_address(instance, 3, SLOT_THIRD) = left < right;

                instance->instruction += 4;
            }
            break;

            case OPCODE_EQUALS:
            {
                Word left = *emulator_address(instance, 1, SLOT_FIRST);
                Word right = *emulator_address(instance, 2, SLOT_SECOND);

                *emulator_address(instance, 3, SLOT_THIRD) = left == right;

                instance->instruction += 4;
            }
            break;

            case OPCODE_OFFSET:
                instance->offset += *emulator_address(instance, 1, SLOT_FIRST);
                instance->instruction += 2;
                break;

            case OPCODE_TERMINATE: return false;
        }
    }
}

void emulator_reimage(Emulator instance, Word image[], int imageSize)
{
    instance->instruction = instance->memory;
    instance->offset = 0;

    memcpy(instance->memory, image, imageSize * sizeof(Word));
    queue_clear(&instance->inputs);
    queue_clear(&instance->outputs);
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

void queue_clear(Queue instance)
{
    instance->first = -1;
    instance->last = -1;
}
