// Licensed under the MIT license.

#include <assert.h>
#include <string.h>
#include "../lib/emulator.h"
#include "../lib/parser.h"
#define EXCEPTION_IO "Error: I/O.\n"
#define MEMORY 10000

int main(int count, ZString args[])
{
    if (count < 3)
    {
        printf("Usage: emulator <program> <dump>\n");

        return 1;
    }

    Word programMemory[MEMORY];
    Word dumpMemory[MEMORY];
    int programSize = parser_parse_file(args[1], programMemory);

    if (!programSize)
    {
        fprintf(stderr, EXCEPTION_IO);

        return 1;
    }

    int dumpSize = parser_parse_file(args[2], dumpMemory);

    if (!dumpSize)
    {
        fprintf(stderr, EXCEPTION_IO);

        return 1;
    }

    if (programSize != dumpSize)
    {
        printf("Usage: Program size does not match dump size.\n");

        return 1;
    }

    emulator_execute(programMemory);

    int compare = memcmp(programMemory, dumpMemory, programSize * sizeof(int));

    assert(compare == 0);

    printf("Ok.\n");

    return 0;
}
