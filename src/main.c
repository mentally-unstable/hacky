// hello
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "writer.h"
#include "util.h"
#include "def.h"
#include "args.h"

cmd_t current = {
    .type = 0,
    .val = 0,
    .dest = NULL,
    .comp = NULL,
    .jump = NULL,
};

void assemble(char *in, char *out) {
    FILE *fin;
    if ((fin = fopen(in, "r")) == NULL) {
        fprintf(stderr, "*** input file error\n");
        exit(1);
    }

    FILE *fout;
    if ((fout = fopen(out, "wa+")) == NULL) {
        fprintf(stderr, "*** output file error\n");
        exit(1);
    }

    char line[10];
    while (fgets(&line[0], 10, fin)) {
        printf("\n-----------------\n");
        clean(line);

        if (skip(line))
            continue;

        current.type = cmd_type(line);
        update_cmd(&current, line);

        printf("CURRENT {%s, %i,  %s, %s, %s}\n",
                enumstr(current.type), current.val,
                current.dest, current.comp, current.jump);

        write_cmd(&current, fout);
    }

    fclose(fin);
    fclose(fout);
}


int main(int argc, char **argv)
{
    args_t *args = argparse(argc, argv);
    assemble(args->in, args->out);

    return 0;
}
