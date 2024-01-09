// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdbool.h>
#include "word.h"

struct Queue
{
    long long* items;
    int first;
    int last;
    int capacity;
};

struct Emulator
{
    long long* memory;
    long long* instruction;
    long long scratchRegister;

    bool (*input)(struct Emulator* instance, long long* result);
    void (*output)(struct Emulator* instance, long long value);

    struct Queue inputs;
    struct Queue outputs;
    int offset;
};

typedef struct Emulator* Emulator;
typedef struct Queue* Queue;

void emulator(Emulator instance, Word memory[]);
bool emulator_execute(Emulator instance);
void emulator_reimage(Emulator instance, Word image[], int imageSize);

void queue(Queue instance, Word buffer[], int capacity);
void queue_enqueue(Queue instance, Word item);
bool queue_try_dequeue(Queue instance, Word* result);
void queue_clear(Queue instance);
