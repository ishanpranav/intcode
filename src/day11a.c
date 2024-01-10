// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Space Police Part 1

#include <stdlib.h>
#include "../lib/parser.h"
#include "day11.h"

int main(void)
{
    Matrix matrix = calloc(DIMENSION * DIMENSION, sizeof * matrix);

    if (!matrix)
    {
        fprintf(stderr, "Error: Out of memory.\n");

        return 1;
    }

    int total = day11_robot(matrix, false);

    printf("11a %d\n", total);
    free(matrix);

    return 0;
}
