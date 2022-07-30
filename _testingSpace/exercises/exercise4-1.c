#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    int fd, bytesRead, numWritten;
    char *outputFile;
    int opt;
    int wflags = O_WRONLY | O_CREAT | O_TRUNC;
    char c;

    ssize_t result;

    printf("argc: %d\n", argc);

    if ((argc != 2) && (argc != 3)){
        printf("Usage: testing [-a] outputFile\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
        outputFile = argv[1];

    if (argc == 3)
        outputFile = argv[2];

    while ((opt = getopt(argc, argv, "a")) != -1){
        switch(opt){
            case 'a':
            case 'A':
                wflags = O_WRONLY | O_CREAT | O_APPEND;
                break;
            case '?':
                printf("unknown option: %c\n", opt);
        }
    }

    fd = open(outputFile, wflags, 0777);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    while((bytesRead = read(STDIN_FILENO, &c, sizeof(c))) > 0){
        if ((numWritten = write(fd, &c, sizeof(c))) == -1){
            perror("write");
            exit(EXIT_FAILURE);
        }
        if ((numWritten = write(STDOUT_FILENO, &c, sizeof(c))) == -1){
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");
    close(fd);
    exit(EXIT_SUCCESS);
}