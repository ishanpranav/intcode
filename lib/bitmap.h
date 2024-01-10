// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include "../include/qdbmp.h"
#include "z_string.h"

typedef BMP* Bitmap;

Bitmap bitmap(long width, long height);

void bitmap_set(
    Bitmap instance, 
    int x,
    int y, 
    unsigned char r, 
    unsigned char g, 
    unsigned char b);

void bitmap_save(Bitmap instance, ZString path);
void finalize_bitmap(Bitmap instance);
