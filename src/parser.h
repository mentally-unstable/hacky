// hello
#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

typedef struct {
    int type;
    int val;
    char *dest;
    char *comp;
    char *jump;
} inst;
// global current word
inst current = {
    .type = 0,
    .val = 0,
    .dest = NULL,
    .comp = NULL,
    .jump = NULL,
};


struct branch {
    inst* statement;
    struct branch *next;
};


struct branch *add(struct branch *trunk, inst state);
void symbol_type(char *str);
void value(char *str);
void parse_current(char *str);
struct branch *parse_lines(char *name);
void write_free(struct branch *tree, char *out);

#endif
