// hello
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "def.h"
#include "util.h"

/*
@2
D=M+1

v
v

ACMD, 2
CCMD, "D", "M+1", null

v
v

bin(2)
dest("D") ^ comp("M+1") ^ 0
*/

// could be changed(?)
void update_cmd(cmd_t *current, char *str) {
    if (current->type == ACMD) {
        current->val = value(str);
        return;
    }

    // if LCMD

    char *strmut = strdup(str);

    if (strchr(str, '='))
        current->dest = strsep(&strmut, "=");


    if (strchr(str, ';')) {
        current->comp = strsep(&strmut, ";");
        current->jump = strmut;
    } else {
        current->comp = strmut;
    }
}


int cmd_type(char *str) {
    if (strchr(str, '@'))
        return ACMD;

    else if (strchr(str, '('))
        return LCMD;

    else if (strchr(str, '=') || strchr(str, ';'))
        return CCMD;

    else {
        fprintf(stderr, "*** parse (lex) error no symbol found for `%s`\n", str);
        exit(1);
    }
}

int value(char *str) {
    char *c = strchr(str, '@');
    char *val = c+1;
    return atoi(val);
}
