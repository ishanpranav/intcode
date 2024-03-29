// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include "parser.h"

int parser_parse(FILE* stream, Word memory[])
{
    Word word;
    int size = 0;

    while (fscanf(stream, WORD_FORMAT ", ", &word) == 1)
    {
        memory[size] = word;
        size++;
    }

    return size;
}

int parser_parse_file(ZString path, Word memory[])
{
    FILE* stream = fopen(path, "r");

    if (!stream)
    {
        return 0;
    }

    int size = parser_parse(stream, memory);

    if (fclose(stream) == EOF)
    {
        return 0;
    }

    return size;
}
