#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void fatal(int err, const char *msg){
    if (!err) return;
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
