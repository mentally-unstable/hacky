// hello
#include <stdlib.h>

#include "util.h"
#include "writer.h"
#include "parser.h"
#include "assemble.h"

#define SYS_RAM 15
#define MAXCHARS 80

void assemble(FILE *fin, FILE *fout) {
    entry_t *table = init_table();
    char line[MAXCHARS];

    // first stage/pass
    user_symbols(table, &line[0], fin);

    // second stage/pass
    int ram = SYS_RAM+1;
    while (fgets(&line[0], MAXCHARS, fin)) {
        cmd_t current = {
            .type = 0,
            .val = 0,
            .dest = NULL,
            .comp = NULL,
            .jump = NULL,
        };

        clean(line);

        if (skip(line)) {
            continue;
        }

        current.type = cmd_type(line);
        update_state(table, ram, &current, line);
        write_cmd(&current, fout);
    }

    free_table(table);
}

void user_symbols(entry_t *head, char *line, FILE *fin) {
    int pos = 0;
    char *label;

    while (fgets(line, MAXCHARS, fin)) {
        clean(line);

        if (skip_empty(line))
            continue;

        if (cmd_type(line) == LCMD) {
            label = label_of(line, LCMD);
            add_entry(head, label, pos);
            continue;
        }

        pos++;
    }

    rewind(fin);
}

void update_state(entry_t *table, int addr, cmd_t *current, char *str) {
    if (current->type == ACMD) {
        current->val = value(str);
        return;
    }

    char *label;
    if (current->type == LREF) {
        label = label_of(str, LREF);

        if (exists(table, label)) {
            current->val = addressof(table, label);

        } else {
            label = label_of(str, CONST);
            add_entry(table, label, addr);

            addr++;
        }

        return;
    }

    split_line(current, str);
}

