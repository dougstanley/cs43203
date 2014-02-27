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
    long pos = 0;

    //open the wtmp file
    utmpfile = fopen("/var/log/wtmp","r");

    //seek ahead in file to third entry
    fseek(utmpfile, 2 * (sizeof(struct utmp)), SEEK_SET);

    //read one utmp struct out of the file
    fread(&ut, sizeof(struct utmp), 1, utmpfile);

    //print out the username field from the struct
    printf("%s\t%s\n", ut.ut_user,ut.ut_line);

    //seek to last record
    fseek(utmpfile, -1 * (sizeof(struct utmp)), SEEK_END);
    pos = ftell(utmpfile);

    //read one utmp struct out of the file
    fread(&ut, sizeof(struct utmp), 1, utmpfile);

    //print out the username field from the struct
    printf("%s\t%s\n", ut.ut_user,ut.ut_line);

    //close it up
    fclose(utmpfile);
    return 0;
}
