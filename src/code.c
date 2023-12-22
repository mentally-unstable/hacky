// hello
/*
 * 0b101
 * ^ 0b000000a
 * << bitnum
 * = bit extended
 *
 * 0b0000000000000010 [JMP]
 * 0b0000000000110000 [DEST]
 * ^XOR- and then they're glued
*/

#include <stdio.h>
#include <string.h>
#include "code.h"

int3 dest(char *mne) {
    unsigned _BitInt(3) dest = 0;

    char *c = mne;
    for (int i = 0; i < 3; ++i) {
        if (*(c+i) == 'M')
            dest |= 1;

        if (*(c+i) == 'D')
            dest |= (1 << 1);

        if (*(c+i) == 'A')
            dest |= (1 << 2);
    }

    return dest;
}

int3 jump(char *mne) {
    unsigned _BitInt(3) jump = 0;

    char *c = mne;

    if (!strcmp(c, "JMP"))
        return 0b111;

    if (!strcmp(c, "JNE"))
        return 0b101;

    if (*(c+1) == 'G')
        jump |= (1);

    if ( (*(c+1) == 'E') || (*(c+2) == 'E') )
        jump |= (1 << 1);

    if (*(c+1) == 'L')
        jump |= (1 << 2);

    return jump;
}

int7 comp(char *m) {
    int7 a = 0b0000000;
    if (strchr(m, 'D'))
        a = 0b1000000;

    unsigned _BitInt(6) c;

    if (!strcmp(m, "0"))
        c = 0b101010;
    else if (!strcmp(m, "1"))
        c = 0b111111;
    else if (!strcmp(m, "-1"))
        c = 0b111010;
    else if (!strcmp(m, "A") || !strcmp(m, "M"))
        c = 0b110000;
    else if (!strcmp(m, "D"))
        c = 0b001100;
    else if (!strcmp(m, "!A") || !strcmp(m, "!M"))
        c = 0b110001;
    else if (!strcmp(m, "!D"))
        c = 0b001101;
    else if (!strcmp(m, "-A") || !strcmp(m, "-M"))
        c = 0b110011;
    else if (!strcmp(m, "-D"))
        c = 0b001111;
    else if (!strcmp(m, "D+1"))
        c = 0b011111;
    else if (!strcmp(m, "A+1") || !strcmp(m, "M+1"))
        c = 0b110111;
    else if (!strcmp(m, "D-1"))
        c = 0b001110;
    else if (!strcmp(m, "A-1") || !strcmp(m, "M-1"))
        c = 0b110010;
    else if (!strcmp(m, "D+A") || !strcmp(m, "D+M"))
        c = 0b000010;
    else if (!strcmp(m, "D-A") || !strcmp(m, "D-M"))
        c = 0b010011;
    else if (!strcmp(m, "A-D") || !strcmp(m, "M-D"))
        c = 0b000111;
    else if (!strcmp(m, "D&A") || !strcmp(m, "D&M"))
        c = 0b000000;
    else if (!strcmp(m, "D|A") || !strcmp(m, "D|M"))
        c = 0b010101;
    else {
        return 0b0010000; // error
    }

    return (int7) a ^ c;
}
