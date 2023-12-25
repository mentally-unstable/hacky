// hello
#ifndef ARGS_INCLUDE
#define ARGS_INCLUDE

typedef struct {
    char *in;
    char *out;
    int hex;
} args_t;

args_t *argparse(int argc, char **argv);
void usage(char *cmd);

#endif
