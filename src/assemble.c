// hello
#include "util.h"
#include "writer.h"
#include "parser.h"
#include "assemble.h"

#define SYS_RAM 16

/*
 * a 0
 * (aadsf) 1  -> aadsf, 1
 * a;jgt 2
 * jump aadsf --> jump 1
 */

void assemble(FILE *fin, FILE *fout) {
    entry_t *table = init_table();
    cmd_t current = {
        .type = 0,
        .val = 0,
        .dest = NULL,
        .comp = NULL,
        .jump = NULL,
    };

    char line[10];
    char *label;

    // first stage
    user_symbols(table, &line[0], fin);

    // second stage
    int ram = SYS_RAM+1;
    while (fgets(&line[0], 10, fin)) {
        clean(line);

        printf("\n-----------------\n");
        if (skip(line))
            continue;

        current.type = cmd_type(line);

        if (current.type == LCMD)
            continue;

        update_state(table, &current, line);

        if (current.type == VARR) {
            label = label_of(line, VARR);
            add_entry(table, label, ram);
            ram++;
            continue;
        }

        printf("CURRENT {%s, %i,  %s, %s, %s}\n",
                enumstr(current.type), current.val,
                current.dest, current.comp, current.jump);

        write_cmd(&current, fout);
    }
}

void user_symbols(entry_t *table, char *line, FILE *fin) {
    int pos = 0;
    char *label;

    while (fgets(line, 10, fin)) {
        clean(line);

        if (skip(line))
            continue;

        if (cmd_type(line) == LCMD) {
            label = label_of(line, LCMD);
            add_entry(table, label, pos);
            continue;
        }

        pos++;
    }

    rewind(fin);
}
