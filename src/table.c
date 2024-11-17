// hello
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "table.h"

entry_t *init_table() {
    entry_t *new = (entry_t *) malloc(sizeof(entry_t));

    char *defaults1[13] = {
        "SP", "LCL", "ARG", "THIS", "THAT",
        "T1", "T2", "T3", "T4",
        "T5", "T6", "T7", "T8",
    };

    char *defaults2[16] = {
        "R0", "R1", "R2", "R3", "R4", "R5",
        "R6", "R7", "R8", "R9", "R10", "R11",
        "R12", "R13", "R14", "R15",
    };

    for (int i = 0; i < 16; i++) {
        if (i < 13)
            add_entry(new, defaults1[i], i);

        add_entry(new, defaults2[i], i);
    }

    add_entry(new, "SCREEN", 16384);
    add_entry(new, "KBD", 24576);

    entry_t *next = new->next;
    free(new);
    return next;
}

int exists(entry_t *entry, char *name) {
    entry_t *p = entry;
    for (; p != NULL; p = p->next) {
        if (!strcmp(p->name, name)) {
            return 1;
        }
    }

    return 0;
}

void add_entry(entry_t *table, const char *s, int a) {
    entry_t *new = (entry_t *) malloc(sizeof(entry_t));

    new->name = s;
    new->addr = a;
    new->next = NULL;

    entry_t *end = seek_end(table);
    end->next = new;
}

entry_t *seek_end(entry_t *head) {
    entry_t *p = head;
    for (; p->next != NULL; p = p->next) ;
    return p;
}

int addressof(entry_t *table, char *name) {
    entry_t *p = table;
    for (; p != NULL; p = p->next) {
        if (!strcmp(p->name, name))
            return p->addr;
    }

    return 0; // should never occur
}

void free_table(entry_t *head) {
    for (; head != NULL; head = head->next) {
        free(head);
    }
}
