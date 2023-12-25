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
            break;
        case CCMD:
            return "CCMD";
            break;
        default:
            fprintf(stderr, "*** util error: unrecognized type `%i`\n", type);
            exit(1);
    }
}

int skip(char *state) {
    if ((*(state) == '#') || !strcmp(state, ""))
        return 1;
    return 0;
}

/* stackoverflow code lol, all slightly edited */
void clean(char *s) {
    char* d = s;
    do {
        while ((*d == '\n') || (*d == ' ')) {
            ++d;
        }
    } while ((*s++ = *d++));
}

void printbits(int x) {
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0'+((x >> (i-1)) & 1));
    putchar('\n');
}

char *bits(unsigned int val, char *buff, int sz) {
    char *pbuff = buff;

    if (sz < 1) return NULL;

    pbuff += sz;
    *pbuff-- = '\0';

    for (int i = 0; i < sz; i++) {
        *pbuff-- = ((val & 1) == 1) ? '1' : '0';

        val >>= 1;
    }

    return pbuff+1;
}

