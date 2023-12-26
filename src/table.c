// hello
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "table.h"

entry_t *init_table() {
    entry_t *new = (entry_t *) malloc(sizeof(entry_t));

    char *defaults1[7] = {
        "SP", "LCL", "ARG", "THIS", "THAT",
        "SCREEN", "KBD",
    };

    char *defaults2[16] = {
        "R0", "R1", "R2", "R3", "R4", "R5",
        "R6", "R7", "R8", "R9", "R10", "R11",
        "R12", "R13", "R14", "R15",
    };

    for (int i = 0; i < 16; i++) {
        if (i < 7)
            add_entry(new, defaults1[i], i);
        add_entry(new, defaults2[i], i);
    }

    return new->next;
}

int exists(entry_t *entry, char *name) {
    fprintf(stdout, "\t<t> checking if `%s` exists\n", name);
    entry_t *p = entry;
    for (; p != NULL; p = p->next) {
        if (!strcmp(p->name, name)) {
            fprintf(stdout, "\t\t<t> found it\n");
            return 1;
        }
    }

    fprintf(stdout, "\t\t<t> didn't find it\n");
    return 0;
}

void add_entry(entry_t *table, char *s, int a) {
    entry_t *new = (entry_t *) malloc(sizeof(entry_t));

    new->name = s;
    new->addr = a;
    new->next = NULL;

    table->next = new;
}

int addressof(entry_t *table, char *name) {
    entry_t *p = table;
    for (; p != NULL; p = p->next) {
        if (!strcmp(p->name, name))
            return p->addr;
    }

    return 0; // should never occur
}
