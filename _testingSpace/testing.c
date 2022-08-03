#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tlpi_hdr.h"

extern char **environ;

int mySetEnv(const char *name, const char *value, int overwrite){
    int strLength = strlen(name) + strlen(value) + 1;
    char newStr[strLength];
    strcat(newStr, name);
    strcat(newStr, "=");
    strcat(newStr, value);

    printf("Value entered to puts: %s\n", newStr);

    if(getenv(name) != NULL && overwrite == 0)
        printf("Cannot overwrite value\n");
    else
        putenv(newStr);
}

void printenv(){
    char **e;

    for (e = environ; *e != NULL; e++)
        printf("%s\n", *e);
}

int myUnSetEnv(const char *name){
    int length = strlen(name);

    for (int i = 0; environ[i] != NULL; i++){
        if(strncmp(environ[i], name, length) == 0){
            for (int j = 0; environ[i+j] != NULL; j++){
                //printf("Old value at position %d: %s\n", (i + j), environ[i + j]);
                environ[i + j] = environ[i + j + 1];
                //printf("New value at position %d: %s\n", (i + j), environ[i+j]);
            }
        }
    }
}

int main(){
    char* arg = "SHELL";
    char* result;

    if ((result = getenv(arg)) == NULL)
        printf("No value for %s\n", arg);
    else
        printf("Result: %s\n", result);

    myUnSetEnv("SHELL");
    
    if ((result = getenv(arg)) == NULL)
        printf("No value for %s\n", arg);
    else
        printf("Result: %s\n", result);    
    exit(EXIT_SUCCESS);
}