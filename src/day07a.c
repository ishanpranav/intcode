// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Amplification Circuit Part 1

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define INPUTS 2
#define MEMORY 4096
#define OUTPUTS 100

struct PermutationIterator
{
    int* values;
    int length;
    bool end;
};

typedef struct PermutationIterator* PermutationIterator;

static void swap(int* p, int* q)
{
    int swap = *p;

    *p = *q;
    *q = swap;
}

void permutation_begin(int* values, int length, PermutationIterator iter)
{
    iter->end = false;
    iter->length = length;
    iter->values = values;
}

void permutation_next(PermutationIterator iter)
{
    int last = iter->length - 1;

    while (last > 0 && iter->values[last - 1] >= iter->values[last])
    {
        last--;
    }

    if (last > 0)
    {
        int index = iter->length - 1;

        while (index > last && iter->values[index] <= iter->values[last - 1])
        {
            index--;
        }

        swap(iter->values + last - 1, iter->values + index);
    }

    int max = (iter->length - last) / 2;

    for (int index = 0; index < max; index++)
    {
        swap(
            iter->values + last + index,
            iter->values + iter->length - 1 - index);
    }

    iter->end = !last;
}

int main()
{
    Word max = 0;
    Word programMemory[MEMORY];
    Word sharedMemory[5][MEMORY];
    Word inputs[5][INPUTS];
    Word outputs[5][OUTPUTS];
    struct PermutationIterator iter;
    struct Emulator amplifiers[5];
    int set[] = { 0, 1, 2, 3, 4 };
    clock_t start = clock();
    int length = parser_parse(stdin, programMemory);

    for (permutation_begin(set, 5, &iter); !iter.end; permutation_next(&iter))
    {
        for (int i = 0; i < 5; i++)
        {
            memcpy(sharedMemory[i], programMemory, length * sizeof(Word));
            emulator(amplifiers + i, sharedMemory[i]);
            queue(&amplifiers[i].inputs, inputs[i], INPUTS);
            queue(&amplifiers[i].outputs, outputs[i], OUTPUTS);
        }

        Word output = 0;

        for (int i = 0; i < 5; i++)
        {
            queue_enqueue(&amplifiers[i].inputs, set[i]);
            queue_enqueue(&amplifiers[i].inputs, output);
            emulator_execute(amplifiers + i);

            output = amplifiers[i].outputs.items[amplifiers[i].outputs.first];
        }

        if (output > max)
        {
            max = output;
        }
    }

    printf(
        "07a " WORD_FORMAT " %lf\n",
        max,
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
