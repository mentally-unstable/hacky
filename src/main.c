// hello
#include <stdio.h>
#include <stdlib.h>

#include "assemble.h"
#include "args.h"

int main(int argc, char **argv)
{
    args_t *args = argparse(argc, argv);

    FILE *fin;
    if ((fin = fopen(args->in, "r")) == NULL) {
        fprintf(stderr, "*** input file error\n");
        exit(1);
    }

    FILE *fout;
    if ((fout = fopen(args->out, "wa+")) == NULL) {
        fprintf(stderr, "*** output file error\n");
        exit(1);
    }

    assemble(fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}
