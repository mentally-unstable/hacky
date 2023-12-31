// hello
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "def.h"
#include "info.h"
#include "args.h"

void info(const char *fmt, ...) {
    if (!args.info)
        return;

    va_list vargs;
    va_start(vargs, fmt);
    vfprintf(stdout, fmt, vargs);
    va_end(vargs);

    fflush(stdout);
}
