// hello
#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

#include "def.h"
#include "table.h"

void split_line(cmd_t *cur, char *str);
int cmd_type(char *str);
int value(char *str);
char *label_of(char *str, int type);
int skip(char *state);
void clean(char *s);
int clean_comment(char *p);

#endif
