// hello
#include <stdio.h>
#include <parser.h>

int main(int argc, char **argv) {
    FILE *input;
    if (argc > 1)
        input = fopen(argv[1]);

    node **tree = parse(input);

    return 0;
}
