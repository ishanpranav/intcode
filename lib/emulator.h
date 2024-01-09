// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include "word.h"

struct Emulator
{
    long* memory;

    long (*input)(void);
    void (*ouput)(long value);
};

typedef struct Emulator* Emulator;

void emulator_execute(Emulator instance);
