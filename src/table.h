// hello
#ifndef TABLE_INCLUDE
#define TABLE_INCLUDE

struct entry_t {
    char *name;
    int  addr;
    struct entry_t *next;
};
typedef struct entry_t entry_t;

entry_t *init_table();
int exists(entry_t *entry, char *name);
void add_entry(entry_t *table, char *s, int a);
int addressof(entry_t *table, char *name);

#endif
