// hello
#include "util.h"
#include <stdio.h>

int main(void) {
    int num = 7;
    char buff[17];
    char *bin;
    bin = bits(num, bin, 16);
    printf("%s\n", bin);
    printf("%i\n", num);
    return 0;
}
