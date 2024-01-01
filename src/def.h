// hello
#ifndef DEF_INCLUDE
#define DEF_INCLUDE

enum {
    ACMD = 1,
    LCMD,
    LREF,
    CONST, // internal compiler flag
    CCMD,
};

typedef struct {
    int type;
    int val;
    char *dest;
    char *comp;
    char *jump;
} cmd_t;

#define BITS 16

#endif
