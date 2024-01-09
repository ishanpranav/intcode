// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdbool.h>
#include "word.h"
#define EMULATOR_INPUTS_CAPACITY 2
#define EMULATOR_OUTPUTS_CAPACITY 1

struct Emulator
{
    long* memory;

    long (*input)(struct Emulator* instance);
    void (*output)(struct Emulator* instance, long value);

    long inputs[EMULATOR_INPUTS_CAPACITY];
    long outputs[EMULATOR_OUTPUTS_CAPACITY];
    int firstInput;
    int lastInput;
    int outputCount;
};

typedef struct Emulator* Emulator;

void emulator(Emulator instance, Word memory[]);
void emulator_input(Emulator instance, Word value);
void emulator_execute(Emulator instance);
