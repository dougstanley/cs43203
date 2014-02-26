/**
 * utmp.c
 *
 * A very simple example of opening up a
 * well known binary file and reading
 * struct's out of it.
 *
 */
#include <utmp.h>
#include <stdio.h>

int main(){
    FILE *utmpfile;
    struct utmp ut;

    //open the wtmp file
    utmpfile = fopen("/var/log/wtmp","r");

    //read one utmp struct out of the file
    fread(&ut, sizeof(struct utmp), 1, utmpfile);

    //close it up
    fclose(utmpfile);

    //print out the username field from the struct
    printf("%s\n", ut.ut_user);

    return 0;
}
