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
    pwrite_lines("../x.asm", "out.hack");
    return 0;
}

void symbol_type(char *str) {
    if (strchr(str, '@'))
        current.type = ACMD;

    else if (strchr(str, '('))
        current.type = LCMD;

    else if (strchr(str, '=') || strchr(str, ';'))
        current.type = CCMD;

    else {
        fprintf(stderr, "*** parse (lex) error no symbol found for `%s`\n", str);
        exit(1);
    }
}

void value(char *str) {
    char *c = strchr(str, '@');

    if (!c) {
        fprintf(stderr, "*** parse error `%s` not an ACMD\n", str);
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

void pwrite_lines(char *in, char *out) {
    FILE *fin;
    if ((fin = fopen(in, "r")) == NULL) {
        fprintf(stderr, "*** input file error\n");
        exit(1);
    }

    FILE *fout;
    if ((fout = fopen(out, "wa+")) == NULL) {
        fprintf(stderr, "*** output file error\n");
        exit(1);
    }

    char statement[10];
    while (fgets(&statement[0], 10, fin)) {
        printf("------------------\n");
        clean(statement);
/*        if (skip(statement))
            continue;*/

        symbol_type(statement);
        parse_current(statement);

        write(current, fout);

        printf("CMD  {%i(%s), %i, %s, %s, %s}\n",
                current.type,
                enumstr(current.type),
                current.val,
                current.dest,
                current.comp,
                current.jump);
    }

    fclose(fin);
    fclose(fout);
}

#define BITS 16
void write(inst statement, FILE *out) {
    char buff[BITS+1];
    char *bin;
    int num;

    switch (statement.type) {
        // case LCMD:
        case ACMD:
            bin = bits(statement.val, buff, BITS);
            break;
        case CCMD:
            num = binary(statement);
            bin = bits(num, buff, BITS);
            break;
        default:
            fprintf(stderr, "*** write error: cannot write statement of type `%s`\n",
                    enumstr(statement.type));
    }

    fprintf(out, "%s\n", bin);
}

int binary(inst state) {
    unsigned _BitInt(16) num = 0b0000000000000000;
    num ^= dest(state.dest);
    num <<= DEST_BITS;

    num ^= comp(state.comp);
    num <<= COMP_BITS;

    num ^= jump(state.jump);

    return (int) num;
}

