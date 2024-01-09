// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdbool.h>
#include "word.h"

struct Queue
{
    long* items;
    int first;
    int last;
    int capacity;
};

struct Emulator
{
    long* memory;

    bool (*input)(struct Emulator* instance, long* result);
    void (*output)(struct Emulator* instance, long value);

    struct Queue inputs;
    struct Queue outputs;
};

typedef struct Emulator* Emulator;
typedef struct Queue* Queue;

void emulator(Emulator instance, Word memory[]);
void emulator_execute(Emulator instance);

void queue(Queue instance, Word buffer[], int capacity);
void queue_enqueue(Queue instance, Word item);
bool queue_try_dequeue(Queue instance, Word* result);
