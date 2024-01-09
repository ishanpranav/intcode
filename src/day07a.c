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
#define MEMORY 4096

Word result;

static void swap(int* p, int* q)
{
    int temp = *p;

    *p = *q;
    *q = temp;
}

void math_permute5(int* set, void (*process)(int* set))
{
    int i = 0;
    int indexes[5] = { 0 };

    process(set);

    while (i < 5)
    {
        if (indexes[i] < i)
        {
            if (i % 2 == 1)
            {
                swap(set + i, set + indexes[i]);
            }
            else
            {
                swap(set + i, set);
            }

            process(set);

            indexes[i]++;
            i = 1;
        }
        else
        {
            indexes[i++] = 0;
        }
    }
}

struct Permutation5Iterator
{
    int* next;
    int current[5];
    int directions[5];
};

typedef struct Permutation5Iterator* Permutation5Iterator;

static Word emulator_on_input()
{
    return 5;
}

static void emulator_on_output(Word value)
{
    result = value;
}

void prints(int* l)
{
    printf("%d %d %d %d %d\n", l[0], l[1], l[2], l[3], l[4]);
}

int main()
{
    int set[] = { 0, 1, 2, 3, 4 };
    int indexes[5] = { 0 };

    Iterator iter;
    iter_begin(set, &iter, indexes, 5);

    while (!iter_end(&iter)) {
        prints(iter.current);
        iter_next(&iter);
    }

    Word programMemory[MEMORY];
    Word sharedMemory[5][MEMORY];
    clock_t start = clock();
    int length = parser_parse(stdin, programMemory);

    struct Emulator emulators[5];

    for (int i = 0; i < 5; i++)
    {
        emulators[i].input = emulator_on_input;
        emulators[i].ouput = emulator_on_output;
        emulators[i].memory = sharedMemory[i];
    }

    math_permute5(set, prints);

    for (int i = 0; i < 5; i++)
    {
        memcpy(sharedMemory, programMemory, length * sizeof(Word));
    }

    printf(
        "05b " WORD_FORMAT " %lf\n",
        result,
        (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
