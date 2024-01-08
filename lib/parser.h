#include <stdio.h>
#include "word.h"
#include "z_string.h"

int parser_parse(FILE* stream, Word memory[]);
int parser_parse_file(ZString path, Word memory[]);
