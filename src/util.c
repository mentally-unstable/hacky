// hello
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "enum.h"

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

    if (val == 0) {
        *pbuff++ = '0';
        *pbuff = '\0';
        return buff;
    }

    pbuff += sz;
    *pbuff-- = '\0';

    for (int i = 0; i < sz; i++) {
        *pbuff-- = ((val & 1) == 1) ? '1' : '0';

        val >>= 1;
    }

    return pbuff+1;
}

