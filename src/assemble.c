// hello
#include <stdlib.h>

#include "util.h"
#include "writer.h"
#include "parser.h"
#include "assemble.h"
#include "info.h"

#define SYS_RAM 15
#define MAXCHARS 80

void assemble(FILE *fin, FILE *fout) {
    entry_t *table = init_table();
char line[MAXCHARS];
    char *label;

    // first stage
    user_symbols(table, &line[0], fin);
    info("<a> built user symbol table\n");
    print_table(table);

    int ram = SYS_RAM+1;
    int i = -1; // assembler index (in file)

    // second stage
    while (fgets(&line[0], MAXCHARS, fin)) {
        cmd_t current = {
            .type = 0,
            .val = 0,
            .dest = NULL,
            .comp = NULL,
            .jump = NULL,
        };

        i++;
        info("--- %i ---\n", i);
        clean(line);

        if (skip(line)) {
            info("<a> [%i] skipping line\n", i);
            continue;
        }

        current.type = cmd_type(line);

        if (current.type == LCMD) {
            info("<a> [%i] skipping label declaration: %s\n", i, line);
            continue;
        }

        update_state(table, &current, line);

        if (current.type == CONST) {
            info("<a> [%i] added constant %s to table at address %i\n", i, line, ram);
            label = label_of(line, CONST);
            add_entry(table, label, ram);

            current.val = ram;
            current.type = LREF; // aaaaa
            ram++;
        }

        info("<a> status: {%s, %i,  %s, %s, %s}\n",
                enumstr(current.type), current.val,
                current.dest, current.comp, current.jump);

        write_cmd(&current, fout);
    }

    free_table(table);
}

void user_symbols(entry_t *head, char *line, FILE *fin) {
    int pos = 0;
    char *label;

    while (fgets(line, MAXCHARS, fin)) {
        clean(line);

        if (skip(line))
            continue;

        if (cmd_type(line) == LCMD) {
            label = label_of(line, LCMD);
            info("<a> adding label `%s`\n", label);
            add_entry(head, label, pos);
            continue;
        }

        pos++;
    }

    rewind(fin);
}
