#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
    int fd = open("myfile.txt", O_APPEND | O_RDWR);
    if (fd == -1)
        perror("open");
    
    lseek(fd, 0, SEEK_SET);

    char* buf = "test";

    ssize_t bytesWritten = write(fd, buf, 4);
}
