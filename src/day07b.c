// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Amplification Circuit Part 2

#include "../lib/emulator.h"
#include "../lib/parser.h"
#include "../lib/permutation_iterator.h"
#define EMULATOR_QUEUE_CAPACITY 5
#define INPUTS 2
#define MEMORY 4096
#define OUTPUTS 1

struct EmulatorQueue
{
    struct Emulator* items[EMULATOR_QUEUE_CAPACITY];
    int first;
    int last;
};

typedef struct EmulatorQueue* EmulatorQueue;

void emulator_queue(EmulatorQueue instance)
{
    instance->first = -1;
    instance->last = -1;
}

void emulator_queue_enqueue(EmulatorQueue instance, Emulator item)
{
    if (instance->first == -1)
    {
        instance->first = 0;
        instance->last = 0;
    }
    else if (instance->first && instance->last == EMULATOR_QUEUE_CAPACITY - 1)
    {
        instance->last = 0;
    }
    else
    {
        instance->last++;
    }

    instance->items[instance->last] = item;
}

Emulator emulator_queue_dequeue(EmulatorQueue instance)
{
    if (instance->first == -1)
    {
        return NULL;
    }

    Emulator result = instance->items[instance->first];

    if (instance->first == instance->last)
    {
        instance->first = -1;
        instance->last = -1;
    }
    else if (instance->first == EMULATOR_QUEUE_CAPACITY - 1)
    {
        instance->first = 0;
    }
    else
    {
        instance->first++;
    }

    return result;
}

int main(void)
{
    Word max = 0;
    Word image[MEMORY];
    Word memory[5][MEMORY];
    Word inputs[5][INPUTS];
    Word outputs[5][OUTPUTS];
    struct PermutationIterator iter;
    struct Emulator amplifiers[5];
    int set[] = { 5, 6, 7, 8, 9 };
    int imageSize = parser_parse(stdin, image);

    for (int i = 0; i < 5; i++)
    {
        emulator(amplifiers + i, memory[i]);
        queue(&amplifiers[i].inputs, inputs[i], INPUTS);
        queue(&amplifiers[i].outputs, outputs[i], OUTPUTS);
    }

    for (permutation_begin(set, 5, &iter); !iter.end; permutation_next(&iter))
    {
        Word output = 0;
        Emulator current;
        struct EmulatorQueue queue;

        emulator_queue(&queue);

        for (int i = 0; i < 5; i++)
        {
            emulator_reimage(amplifiers + i, image, imageSize);
            queue_enqueue(&amplifiers[i].inputs, set[i]);
            emulator_queue_enqueue(&queue, amplifiers + i);
        }

        while ((current = emulator_queue_dequeue(&queue)))
        {
            queue_enqueue(&current->inputs, output);
            
            if (emulator_execute(current))
            {
                emulator_queue_enqueue(&queue, current);
            }

            queue_try_dequeue(&current->outputs, &output);
        }

        if (output > max)
        {
            max = output;
        }
    }

    printf("07b " WORD_FORMAT "\n", max);

    return 0;
}
