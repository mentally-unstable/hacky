// hello
#ifndef ARGS_INCLUDE
#define ARGS_INCLUDE

typedef struct {
    char *in;
    char *out;
    int hex;
    int info;
} args_t;

void argparse(int argc, char **argv);
void usage(char *cmd);

#ifdef LOCAL
#define _extern /**/
#else
#define _extern extern
#endif

_extern args_t args;

#endif
