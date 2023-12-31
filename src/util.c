// hello
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "def.h"

char *enumstr(int type) {
    switch (type) {
        case ACMD:
            return "ACMD";
        case CCMD:
            return "CCMD";
        case LCMD:
            return "LCMD";
        case LREF:
            return "LREF";
        default:
            fprintf(stderr, "*** util error: unrecognized type `%i`\n", type);
            exit(1);
    }
}

int skip(char *state) {
    if (!strcmp(state, ""))
        return 1;

    return 0;
}

void clean(char *s) {
    char *d = s;
    do {
        while ((*d == '\n') || (*d == ' ')) {
            ++d;
        }

        if (*d == '/') {
            if (*(d++) == '/') {
                --d;
                *d = '\0';

            } else {
                fprintf(stderr, "*** util (parse) error: unknown statement `%s`\n", s);
                exit(1);
            }
        }

        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

void printbits(int x) {
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0'+((x >> (i-1)) & 1));
    putchar('\n');
}

char *bits(unsigned int val, char *buff) {
    char *pbuff = buff;

    pbuff += BITS;
    *pbuff-- = '\0';

    for (int i = 0; i < BITS; i++) {
        *pbuff-- = ((val & 1) == 1) ? '1' : '0';

        val >>= 1;
    }

    return pbuff+1;
}

