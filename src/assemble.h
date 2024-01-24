// hello
#ifndef ASSEMBLE_INCLUDE
#define ASSEMBLE_INCLUDE

#include "table.h"
#include "def.h"
#include <stdio.h>

void assemble(FILE *fin, FILE *fout);
void user_symbols(entry_t *table, char *line, FILE *fin);
void update_state(entry_t *table, int addr, cmd_t *current, char *str);

#endif
