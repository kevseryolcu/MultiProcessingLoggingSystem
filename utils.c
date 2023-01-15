#include "utils.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void failChecker(int result, char *message) {
    if(result < 0) {
        perror(message);
        _exit(-1);
    }
}