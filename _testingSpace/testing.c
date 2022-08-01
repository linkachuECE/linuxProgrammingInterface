#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"
#include <stdio.h>

extern char **__environ;

int main(int argc, char *argv[]) {
    char* s = getenv("SOMETHINGSTUPID");

    if (s == NULL){
        printf("No such environment variable\n");
        exit(EXIT_FAILURE);
    } else
        printf("%s\n", s);

    return 0;
}
