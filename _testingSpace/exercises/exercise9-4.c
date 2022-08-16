#include <setjmp.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mcheck.h>
#include <pwd.h>
#include <termios.h>
#include <grp.h>
#include <sys/fsuid.h>
#include <sys/types.h>
#define _GNU_SOURCE

void suspendAndResume(){
    seteuid(getuid());

    uid_t suid, ruid, euid;
    getresuid(&ruid, &euid, &suid);
    printf("Changed EUID to RUID\n");
    printf("Real UID: %d, Effective UID: %d, Saved UID: %d\n", ruid, euid, suid);

    setresuid(-1, suid, -1);
    printf("Changed EUID back\n");
    printf("Real UID: %d, Effective UID: %d, Saved UID: %d\n", ruid, euid, suid);
}

int main(){
    suspendAndResume();
    exit(EXIT_SUCCESS);
}