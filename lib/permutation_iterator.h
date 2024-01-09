// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdbool.h>

struct PermutationIterator
{
    int* values;
    int length;
    bool end;
};

typedef struct PermutationIterator* PermutationIterator;

void permutation_begin(int* values, int length, PermutationIterator iterator);
void permutation_next(PermutationIterator iterator);
