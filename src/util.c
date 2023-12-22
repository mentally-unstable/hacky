// hello
#include <stdlib.h>
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
            return "uuuuhhhhh";
            break;
    }
}

void clean(char *s) {
    char* d = s;
    do {
        while ((*d == '\n') || (*d == ' ')) {
            ++d;
        }
    } while ((*s++ = *d++));
}

