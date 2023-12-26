// hello
#ifndef ASSEMBLE_INCLUDE
#define ASSEMBLE_INCLUDE

#include "table.h"
#include <stdio.h>

void assemble(FILE *fin, FILE *fout);
void user_symbols(entry_t *table, char *line, FILE *fin);

#endif
