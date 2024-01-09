#include <stdlib.h>
#include "../lib/parser.h"
#include "../lib/emulator.h"
#define MEMORY 1048576

Word emulator_on_input()
{
    printf(">> ");

    Word result;

    if (scanf(" " WORD_FORMAT, &result) != 1)
    {
        return 0;
    }

    return result;
}

void emulator_on_output(Word value)
{
    printf("> " WORD_FORMAT "\n", value);
}

int main(int count, ZString args[])
{
    if (count < 2)
    {
        printf("Usage: intcode <program>\n");

        return 1;
    }

    Word* memory = malloc(MEMORY * sizeof(Word));

    if (!memory)
    {
        fprintf(stderr, "Error: Out of memory.\n");

        return 1;
    }

    int length = parser_parse_file(args[1], memory);

    if (!length)
    {
        fprintf(stderr, "Error: Format.\n");

        return 1;
    }

    struct Emulator emulator =
    {
        .input = emulator_on_input,
        .ouput = emulator_on_output,
        .memory = memory
    };

    emulator_execute(&emulator);
    free(memory);
    printf("Ok.\n");

    return 0;
}
