/**********************
 * a very simple
 * ls implementation.
 **********************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/*
  Ok, so there doesn't seem to be a way to use the inode number
  to get stat info, so we have to basically work with strings
  here. So we need a char * big enough to hold the path, plus
  a filename in the path.

  So basically, we use the pathconf function to give us the maximum
  length a filename can be, and we add it to the length of the path
  to the directory we're looking through, then we add 2 more bytes,
  cause we're goint to put a '/' char between the path and the 
  filename, plus we need another char to add a null byte to the end.

  Sadly, we have to do a bunch of string manipulation for this to work.
  It does make sense, being that the only portable way to access file
  info is by using a path, as some systems may not implement inodes, or
  may implement them differently. Since the point of POSIX is to enable
  portability of code between systems, we have to stick to the methods
  that are most portable, and that happens to be working only with paths.
  */
void lsd(char *path){
	DIR *dirp = NULL;
	struct dirent *dent = NULL; 
	struct stat st;

    //lenth of the path to the dir we're processing
    unsigned int pathlen = strlen(path);

    //this tells us the maximum length a filename might be
    unsigned int max_file_len = pathconf(path, _PC_NAME_MAX);
    
    //so this will be the maximum length the full path to any
    //file in this directory will be.
    unsigned int tmp_path_len = pathlen + max_file_len + 2;
    char tmp_path[ tmp_path_len ];

    //clear out the temp path buffer, set all bytes to 0.
    memset(tmp_path,0, tmp_path_len);

    //copy in the bytes from the path
    strcpy(tmp_path,path);
    if( tmp_path[pathlen - 1] != '/' ){
        tmp_path[pathlen] = '/';
        tmp_path[pathlen + 1] = '\0';
        pathlen = strlen(tmp_path);
    }

	dirp = opendir( path );
	while(1){
		dent = readdir(dirp);
		if( dent == NULL ) break;

		if( dent->d_name[0] != '.' ){
            //copy the file name onto the end of the temp path name
            strcat(tmp_path,dent->d_name);

            //now we have the full path to the file we're examining
            //so we can stat it
            stat( tmp_path, &st );

            //print out file size and file name
			printf("%d\t%s\n", st.st_size, dent->d_name);

            //put a null byte back in the string, so that
            //strcat overwrites the filename the next iteration through
            //the loop
            tmp_path[pathlen] = '\0';
		}
	}	
	
	closedir(dirp);
}

int main(int argc, char **argv){

	struct stat st;

    //if no args, list current dir
	if( argc == 1 ){
		lsd( "." );
	}
    //if there's an arg, we see if the arg
    //is a file or a dir. If it's a dir, we
    //pass it to the list directory function
    else if ( argc == 2 ){
		stat( argv[1], &st );

		if( S_ISDIR(st.st_mode) ){
			lsd( argv[1] );
		} else {
            //if it's just a plain file, we print out
            //the stat info for the file.
			printf("%d\t%s\n", st.st_size, argv[1]);
		}
	}

	return 0;
}
