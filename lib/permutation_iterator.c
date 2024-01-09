// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include "permutation_iterator.h"

static void swap(int* p, int* q)
{
    int swap = *p;

    *p = *q;
    *q = swap;
}

void permutation_begin(int* values, int length, PermutationIterator iterator)
{
    iterator->end = false;
    iterator->length = length;
    iterator->values = values;
}

void permutation_next(PermutationIterator iterator)
{
    int last = iterator->length - 1;

    while (last > 0 && iterator->values[last - 1] >= iterator->values[last])
    {
        last--;
    }

    if (last > 0)
    {
        int index = iterator->length - 1;

        while (index > last && 
            iterator->values[index] <= iterator->values[last - 1])
        {
            index--;
        }

        swap(iterator->values + last - 1, iterator->values + index);
    }

    int max = (iterator->length - last) / 2;

    for (int index = 0; index < max; index++)
    {
        swap(
            iterator->values + last + index,
            iterator->values + iterator->length - 1 - index);
    }

    iterator->end = !last;
}
