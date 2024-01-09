#include "word.h"

struct Emulator
{
    long* memory;

    long (*input)(void);
    void (*ouput)(long value);
};

typedef struct Emulator* Emulator;

void emulator_execute(Emulator instance);
