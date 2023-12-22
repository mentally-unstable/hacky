// hello
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "code.h"
#include "parser.h"
#include "enum.h"
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

int main(void) {
    struct branch *to_write = parse_lines("x.asm");
    write_free(to_write, "x.hack");
    return 0;
}

struct branch *add(struct branch *trunk, inst state) {
    struct branch new = { .statement = &state, .next = NULL };
    trunk->next = &new;

    struct branch *ref = &new;
    return ref;
}


void symbol_type(char *str) {
    if (strchr(str, '@'))
        current.type = ACMD;

    else if (strchr(str, '('))
        current.type = LCMD;

    else if (strchr(str, '=') || strchr(str, ';'))
        current.type = CCMD;

    else {
        fprintf(stderr, "RIP BOZO no symbol found for `%s`\n", str);
        exit(1);
    }
}

void value(char *str) {
    char *c = strchr(str, '@');

    if (!c) {
        fprintf(stderr, "RIP BOZO `%s` not an ACMD\n", str);
        exit(1);
    }

    char *val = c+1;
    current.val = atoi(val);
}

void parse_current(char *str) {
    if (current.type != CCMD) {
        value(str);
        return;
    }

    char *strmut = strdup(str);

    if (strchr(str, '='))
        current.dest = strsep(&strmut, "=");


    if (strchr(str, ';')) {
        current.comp = strsep(&strmut, ";");
        current.jump = strmut;
    } else {
        current.comp = strmut;
    }
}

struct branch *parse_lines(char *name) {
    struct branch *cur = (struct branch *) malloc(sizeof(struct branch));
    struct branch *first = cur;

    FILE *fh;
    if ((fh = fopen(name, "r")) == NULL) {
        fprintf(stderr, "file error\n");
        exit(1);
    }

    char statement[10];
    while (fgets(&statement[0], 10, fh)) {
        clean(statement);

        symbol_type(statement);
        parse_current(statement);

        cur = add(cur, current);
        printf("STA  %s\n", statement);
        printf("CMD  {%i(%s), %i, %s, %s, %s}\n",
                current.type,
                enumstr(current.type),
                current.val,
                current.dest,
                current.comp,
                current.jump);
    }

    fclose(fh);
    free(cur);

    return first;
}

void write_free(struct branch *tree, char *out) {
    ;

    free(tree);
}
