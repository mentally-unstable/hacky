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


void parse_current(char *str);
    void symbol_type(char *str);
    void value(char *str);

void pwrite_lines(char *in, char *out);
    void write(inst statement, FILE *out);
    int binary(inst state);

#endif
