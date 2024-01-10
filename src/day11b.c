// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Space Police Part 2

#include <stdlib.h>
#include "../lib/bitmap.h"
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

    day11_robot(matrix, true);
    Bitmap image =  bitmap(DIMENSION, DIMENSION);

    for (int x = 0; x < DIMENSION; x++)
    {
        for (int y = 0; y < DIMENSION; y++)
        {
            if (matrix[x * DIMENSION + y].value)
            {
                bitmap_set(image, x, y, 128, 255, 255);
            }
        }
    }

    bitmap_save(image, "11b.bmp");
    printf("11b: 11b.bmp.\n");
    finalize_bitmap(image);
    free(matrix);

    return 0;
}
