// hello
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "info.h"

#define LOCAL
#include "args.h"
args_t args = {
    .out = NULL,
    .in = NULL,
    .hex = 0,
    .info = 0,
};

void argparse(int argc, char **argv) {
    char msg[64] = "";
    args.out = "a.out";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i-1], "-o") && !strchr(argv[i], '-'))
            args.in = argv[i];

        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
            exit(1);
        }

        if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
            strcat(msg, "<ap> enabled verbose output\n");
            args.info = 1;
        } else
            args.info = 0;

        if (!strcmp(argv[i], "-H") || !strcmp(argv[i], "--hex")) {
            strcat(msg, "<ap> output in hex format\n");
            args.hex = 1;
        } else
            args.hex = 0;

        if (!strcmp(argv[i-1], "-o"))
            args.out = argv[i];
    }

    if (!args.in) {
        fprintf(stderr, "*** args error: no input file provided\n");
        usage(argv[0]);
        exit(1);
    }

    info(msg);
}

void usage(char *cmd) {
    fprintf(stderr,
"Usage:\n$ %s file [options]\n\
options:\n\
\t-o <file>\toutput file name\n\
\t-v|--verbose\tverbose output (for debugging)\n\
\t-H|--hex\thexadecimal output\n\
\t-h|--help\tdisplays this message\n", cmd);
}

