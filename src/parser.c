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

void split_line(cmd_t *current, char *str) {
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
        res += 1;
        res = strsep(&res, ")");

    } else if (type == LREF || type == CONST) {
        res = strsep(&res, "@");
        res += 1;
    }

    return res;
}

int skip(char *state) {
    if (!strcmp(state, ""))
        return 1;

    if (*state == '(')
        return 1;

    return 0;
}

int skip_empty(char *state) {
    if (!strcmp(state, ""))
        return 1;

    return 0;
}

void clean(char *s) {
    char *d = s;
    do {
        while (*d == '\n') {
            ++d;
        }

        while (*d == ' ') {
            ++d;
        }

        if (!clean_comment(d))
        {
            fprintf(stderr, "*** parser error: unknown statement `%s`\n\
\t(hint: did you mean to comment?)\n", s);
            exit(1);
        }
    } while ((*s++ = *d++));
}

int clean_comment(char *d) {
    if (*d == '/') {
        if (*(d++) == '/') {
            --d;
            *d = '\0';
            return 1;
        }

        return 0;
    }

    // redundant but for compiler satisfaction
    return 1;
}
