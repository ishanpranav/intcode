#include <stdlib.h>
#include "../lib/parser.h"
#include "../lib/emulator.h"
#define MEMORY 1048576

bool emulator_on_input(Emulator instance, Word* result)
{
    printf(">> ");

    return scanf(WORD_FORMAT, result) == 1;
}

void emulator_on_output(Emulator instance, Word value)
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

    struct Emulator processor;

    emulator(&processor, memory);

    processor.input = emulator_on_input;
    processor.output = emulator_on_output;;

    emulator_execute(&processor);
    free(memory);
    printf("Ok.\n");

    return 0;
}
