// hello
#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

#include "def.h"

int cmd_type(char *str);
int value(char *str);
void update_cmd(cmd_t *current, char *str);

#endif
