#include <stdio.h>
#include <stdlib.h>

#include "ascii-image/utils.h"

[[noreturn]] void terminate(const char *message, int code)
{
    fprintf(stderr, "%s\n", message);
    exit(code);
}
