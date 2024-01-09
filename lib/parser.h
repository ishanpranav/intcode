// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

#include <stdio.h>
#include "word.h"

typedef char* ZString;

int parser_parse(FILE* stream, Word memory[]);
int parser_parse_file(ZString path, Word memory[]);
