#include "word.h"

struct Emulator
{
    FILE* input;
    FILE* output;
    Word* memory;
};

typedef struct Emulator* Emulator;

void emulator_execute(Emulator instance);
