// hello
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "def.h"
#include "util.h"
#include "table.h"

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

void update_state(entry_t *table, cmd_t *current, char *str) {
    if (current->type == ACMD) {
        fprintf(stdout, "\t<p> reading value of ACMD\n");
        current->val = value(str);
        return;
    }

    char *label;
    if (current->type == LREF) {
        label = label_of(str, LREF);
        /*
         * if ((current->val = addressof(table, label)))
         *     ;
         */
        if (exists(table, label)) {
            fprintf(stdout, "\t<p> reading ROM address (file index) of label\n");
            current->val = addressof(table, label);
        } else {
            fprintf(stdout, "\t<p> set `%s` as variable declaration\n", str);
            current->type = VARR;
        }

        return;
    }

    parse_statement(current, str);
}

void parse_statement(cmd_t *current, char *str) {
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
    char *p;
    if ((p = strchr(str, '@'))) {
        if (isdigit(*(p+1)))
            return ACMD;
        else
            return LREF;
    }

    else if (strchr(str, '('))
        return LCMD;

    else if (strchr(str, '=') || strchr(str, ';'))
        return CCMD;

    else {
        fprintf(stderr, "*** parse (lex) error no symbol found for `%s`\n", str);
        exit(1);
    }
}

// for literals
int value(char *str) {
    char *c = strchr(str, '@');
    char *val = c+1;
    return atoi(val);
}

// for symbols
char *label_of(char *str, int type) {
    char *res = strdup(str);

    if (type == LCMD) {
        res = strsep(&str, "(");
        res = strsep(&str, ")");

    } else if (type == LREF || type == VARR) {
        res = strchr(str, '@');
        res += 1;
    }

    return res;
}
