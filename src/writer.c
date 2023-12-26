// hello
#include <stdlib.h>

#include "writer.h"
#include "util.h"
#include "code.h"

void write_cmd(cmd_t *cmd, FILE *out) {
    char buff[BITS+1];
    char *bin = NULL;
    int num;

    switch (cmd->type) {
        case LCMD:
        case LREF:
        case ACMD:
            bin = bits(cmd->val, &buff[0]);
            break;
        case CCMD:
            num = binary(cmd);
            bin = bits(num, &buff[0]);
            break;
        default:
            fprintf(stderr, "*** write error: cannot write statement of type `%s`\n",
                    enumstr(cmd->type));
    }

    fprintf(out, "%s\n", bin);
}

int binary(cmd_t *cmd) {
    unsigned _BitInt(16) num;
    
    if (uses_memory(cmd->comp))
        num = 0b0000000000001111;
    else
        num = 0b0000000000001110;

    num <<= COMP_BITS;
    num ^= (comp(cmd->comp));

    num <<= DEST_BITS;
    num ^= (dest(cmd->dest));

    num <<= JUMP_BITS;
    num ^= (jump(cmd->jump));

    return (int) num;
}
