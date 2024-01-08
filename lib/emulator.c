#include "emulator.h"
#include "opcode.h"

void emulator_execute(Word memory[])
{
    Word* instruction = memory;

    for (;;)
    {
        switch (*instruction)
        {
            case OPCODE_ADD:
            {
                Word* a = memory + instruction[1];
                Word* b = memory + instruction[2];
                Word* result = memory + instruction[3];

                *result = *a + *b;
                instruction += 4;
            }
            break;

            case OPCODE_MULTIPLY:
            {
                Word* a = memory + instruction[1];
                Word* b = memory + instruction[2];
                Word* result = memory + instruction[3];

                *result = *a * *b;
                instruction += 4;
            }
            break;

            case OPCODE_TERMINATE: return;
        }
    }
}
