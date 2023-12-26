// hello
#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

#include "def.h"
#include "table.h"

int cmd_type(char *str);
int value(char *str);
char *label_of(char *str, int type);
void parse_statement(cmd_t *cur, char *str);
void update_state(entry_t *table, cmd_t *current, char *str);

#endif
