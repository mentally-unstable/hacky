// hello
#ifndef WRITER_INCLUDE
#define WRITER_INCLUDE

#include "def.h"
#include <stdio.h>

void write_cmd(cmd_t *c, FILE *out);
int binary(cmd_t *c);
char *hex(int num);

#endif
