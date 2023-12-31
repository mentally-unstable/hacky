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
#include <stdlib.h>
#include <string.h>
#include "code.h"

int uses_memory(char *m) {
    if (strchr(m, 'M'))
        return 1;
    return 0;
}

int3 dest(char *mne) {
    unsigned _BitInt(3) dest = 0b000;

    if (mne == NULL)
        return dest;

    if (strchr(mne, 'M'))
        dest |= 0b001;

    if (strchr(mne, 'D'))
        dest |= 0b010;

    if (strchr(mne, 'A'))
        dest |= 0b100;

    return dest;
}

int3 jump(char *mne) {
    unsigned _BitInt(3) jump = 0;

    if (mne == NULL)
        return jump;

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

int6 comp(char *m) {
    if (m == NULL) {
        fprintf(stderr, "*** encoder error: no comp in `%s`\n", m);
        exit(1);
    }

    unsigned _BitInt(6) c = 0b000000;

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
        fprintf(stdout, "*** encoder error: unrecognized comp mnemonic `%s`\n", m);
    }

    return c;
}
