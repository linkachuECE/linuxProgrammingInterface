#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/uio.h>

int main(int argc, char *argv[]) {
    int length1 = 64;
    int length2 = 128;
    int length3 = 16;

    char buf1[length1];
    char buf2[length2];
    char buf3[length3];

    struct iovec iostruct[] = {
        {buf1, length1},
        {buf2, length2},
        {buf3, length3}
    };

    int fd = open("myfile.txt", O_RDONLY);
    int wfd = open("output.txt", O_WRONLY | O_TRUNC);
    readv(fd, iostruct, 3);
    writev(wfd, iostruct, 3);
    
    return 0;
}