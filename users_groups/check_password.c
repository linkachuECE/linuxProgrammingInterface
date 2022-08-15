/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2022.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 8-2 */

/* check_password.c

   Read a user name and password and check if they are valid.

   This program uses the shadow password file. Some UNIX implementations
   don't support this feature.
*/
/* Compile with -lcrypt */
#if ! defined(__sun)
#define _BSD_SOURCE     /* Get getpass() declaration from <unistd.h> */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE   /* Get crypt() declaration from <unistd.h> */
#endif
#endif
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "tlpi_hdr.h"

struct passwd *myGetpwnam(const char* nam){
    struct passwd *currPasswd;

    currPasswd = getpwent();
    while(currPasswd != NULL){
        if (strcmp(currPasswd->pw_name, nam) == 0)
            break;
        currPasswd = getpwent();
    }

    return currPasswd;
}

int main(int argc, char *argv[]){
    struct passwd* mypasswd = myGetpwnam("LINKIDO");

    if(mypasswd == NULL)
        puts("Username not found");
    else
        printf("%s has user ID %d\n", mypasswd->pw_name, mypasswd->pw_uid);

    exit(EXIT_SUCCESS);
}
