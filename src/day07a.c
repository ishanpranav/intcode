// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Amplification Circuit Part 1

#include "../lib/emulator.h"
#include "../lib/parser.h"
#include "../lib/permutation_iterator.h"
#define INPUTS 2
#define MEMORY 4096
#define OUTPUTS 1

int main(void)
{
    Word max = 0;
    Word image[MEMORY];
    Word memory[5][MEMORY];
    Word inputs[5][INPUTS];
    Word outputs[5][OUTPUTS];
    struct PermutationIterator iter;
    struct Emulator amplifiers[5];
    int set[] = { 0, 1, 2, 3, 4 };
    int size = parser_parse(stdin, image);

    for (int i = 0; i < 5; i++)
    {
        emulator(amplifiers + i, memory[i]);
        queue(&amplifiers[i].inputs, inputs[i], INPUTS);
        queue(&amplifiers[i].outputs, outputs[i], OUTPUTS);
    }

    for (permutation_begin(set, 5, &iter); !iter.end; permutation_next(&iter))
    {
        Word output = 0;

        for (int i = 0; i < 5; i++)
        {
            emulator_reimage(amplifiers + i, image, size);
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

    printf("07a " WORD_FORMAT "\n", max);

    return 0;
}
