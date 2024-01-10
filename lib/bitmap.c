// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include "bitmap.h"

Bitmap bitmap(long width, long height)
{
    return BMP_Create(width, height, 32);
}

void bitmap_set(
    Bitmap instance, 
    int x,
    int y, 
    unsigned char r, 
    unsigned char g, 
    unsigned char b)
{
    BMP_SetPixelRGB(instance, x, y, r, g, b);
}

void bitmap_save(Bitmap instance, ZString path)
{
    BMP_WriteFile(instance, path);
}

void finalize_bitmap(Bitmap instance)
{
    BMP_Free(instance);
}
