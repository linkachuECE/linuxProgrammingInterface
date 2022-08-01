#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

struct myIovec{
    void* iov_base;
    size_t iov_len;
};

struct myIovec* iovectConstructor(int* lengths, int noOfItems){
    struct myIovec* iovec = malloc(noOfItems * sizeof(*iovec));

    for(int i = 0; i < noOfItems; i++){
        iovec[i].iov_base = (char*) malloc(lengths[i] * sizeof(char));
        iovec[i].iov_len = lengths[i];
    }

    return iovec;
}

ssize_t myWritev(int fd, const struct myIovec *iov, int iovcnt){
    int total = 0;
    for(int i = 0; i < iovcnt; i++){
        int result = write(fd, iov[i].iov_base, iov[i].iov_len);
        if (result == -1){
            perror("Write");
            exit(EXIT_FAILURE);
        }
        total += result;
    }

    return total;
}

ssize_t myReadv(int fd, struct myIovec *iov, int iovcnt){
    int total = 0;
    for(int i = 0; i < iovcnt; i++){
        int result = read(fd, iov[i].iov_base, iov[i].iov_len);
        printf("Text in buffer %d:\n\"%s\"\n\n", i, iov[i].iov_base);
        if (result == -1){
            perror("read");
            exit(EXIT_FAILURE);
        }

        total += result;
    }

    return total;
}

void freeIovec(struct myIovec *iov, int iovcnt){
    for(int i = 0; i < iovcnt; i++)
        free(iov[i].iov_base);
    
    free(iov);
}

int main(int argc, char *argv[]) {
    int lengths[] = {256, 128, 128};
    int rfd, wfd;

    struct myIovec *iovec = iovectConstructor(lengths, 3);

    if ((rfd = open("myfile.txt", O_RDONLY)) == -1)
        perror("open");

    if ((wfd = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777)) == -1)
        perror("open");

    myReadv(rfd, iovec, 3);
    myWritev(wfd, iovec, 3);

    freeIovec(iovec, 3);
}
