// hello
#include <stdio.h>
#include <stdlib.h>

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

void printbits(int x) {
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0'+((x >> (i-1)) & 1));
    putchar('\n');
}

