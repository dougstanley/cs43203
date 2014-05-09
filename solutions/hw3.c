/*
 * catdir.c
 *
 * Takes a single directory as an argument,
 * and concatenates all the regular files
 * in the directory.
 *
 * works similar to:
 * find DIR -type f | xargs cat
 *
 *  Author: Doug Stanley <dmstanle@kent.edu>
 *    Date: 4/15/14
 * Version: 1.0
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_BUFF 4096

int catfile(FILE *);

int main(int argc, char **argv){
    const char *dirname = argv[1];
    
    DIR *dirp = NULL;
	struct dirent *dent = NULL; 
    FILE *fp = NULL;
    struct stat sp;

    int status = 0;

    if( argc != 2 ){
        fprintf(stderr,"Wrong number of args!\n");
        exit(EXIT_FAILURE);
    }

    /* First, stat the dirname given, see if it is a directory */
    status = stat(dirname, &sp);
    if( status != 0 ){
        perror("Stat failed");
        exit(EXIT_FAILURE);
    } else if( ! S_ISDIR(sp.st_mode) ){
        fprintf(stderr,"Argument given is not a directory!\n");
        exit(EXIT_FAILURE);
    }

    /* Ok, at this point, we know that dirname is the name of
     * a directory, so lets open it up and iterate through it.
     */
    dirp = opendir(dirname);
    /* kind of a cheat here, or more like a shortcut.
     * change our working directory to that of the directory
     * we're reading through, that way, we can open any file name
     * by just passing the file name to fopen().
     */
    status = chdir(dirname);
    if( dirp == NULL && status == 0 ){
        perror("Failed to open dir");
        exit(EXIT_FAILURE);
    }
    while(1){
		dent = readdir(dirp);
		if( dent == NULL ) break;
        
        /* do stat on filename, see if it's a regular file. */
        status = stat(dent->d_name, &sp);
        if( status != 0 ){
            perror("Stat failed");
            exit(EXIT_FAILURE);
        } else if( S_ISREG(sp.st_mode) ){
            /* it's a regular file, so open it up, pass it to catfile */
            fp = fopen(dent->d_name,"rb");
            if( fp != NULL ){
                catfile(fp);
            }else{
                perror("Failed to open file");
                exit(EXIT_FAILURE);
            }
            /* done with this file, so close it up */
            fclose(fp);
        }
    }
    /* Done, so close up the dir pointer */
     closedir(dirp);

    return 0;
}

/* Takes an open file pointer, dumps it's content to stdout. */
int catfile(FILE *fp){
    unsigned char buff[MAX_BUFF] = {0};
    int num_in, num_out;

    num_in = num_out = 0;

    if( fp == NULL ) return 1;

    while( ! feof(fp) ){
        num_in = fread(buff,1,MAX_BUFF,fp);
        if( num_in < 1 ) continue;

        num_out = fwrite(buff,1,num_in,stdout);

        if( num_in != num_out ) return 1;
    }
}
