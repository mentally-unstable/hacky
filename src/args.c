// hello
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "args.h"

/*
 * $ hacky mult.asm -o mult.hack [--hex|-H] [--help|-h]
 */
args_t *argparse(int argc, char **argv) {
    args_t *args = (args_t *) malloc(sizeof(args_t));

    args->out = "a.out";

    for (int i = 1; i < argc; i++) {
        if (!strchr(argv[i-1], '-') && !strchr(argv[i], '-'))
            args->in = argv[i];

        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
            exit(1);
        }

        if (!strcmp(argv[i], "-H") || !strcmp(argv[i], "--hex"))
            args->hex = 1;
        else
            args->hex = 0;

        if (!strcmp(argv[i-1], "-o"))
            args->out = argv[i];
    }

    if (!args->in) {
        fprintf(stderr, "*** args error: no input file provided\n");
        usage(argv[0]);
        exit(1);
    }

    return args;
}

void usage(char *cmd) {
    fprintf(stderr,
"Usage:\n$ %s file [-o output] [-H|--hex] [-h|--help]\n\
\t-H|--hex\thexadecimal output\n", cmd);
}

