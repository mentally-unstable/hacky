// hello
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOCAL
#include "args.h"
args_t args = {
    .out = NULL,
    .in = NULL,
    .hex = 0,
};

void argparse(int argc, char **argv) {
    args.out = "out.hack";

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
            exit(1);
        }


        else if (strcmp(argv[i-1], "-o") && !strchr(argv[i], '-')) {
            args.in = argv[i];
            continue;
        }

        else if (!strcmp(argv[i], "-H")) {
            args.hex = 1;
            continue;
        }

        else if (!strcmp(argv[i], "-o")) {
            continue;
        }

        else if (!strcmp(argv[i-1], "-o")) {
            args.out = argv[i];
            continue;
        }

        else {
            fprintf(stderr, "*** args error: unknown argument `%s`\n", argv[i]);
        }
    }

    if (!args.in) {
        fprintf(stderr, "*** args error: no input file provided\n");
        usage(argv[0]);
        exit(1);
    }
}

void usage(char *cmd) {
    fprintf(stderr,
"Usage:\n$ %s file [options]\n\
options:\n\
\t-o <file>\toutput file name\n\
\t-v\t\tverbose output (for debugging)\n\
\t-H\t\thexadecimal output\n\
\t-h|--help\tdisplays this message\n", cmd);
}

