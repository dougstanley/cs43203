/***************
 * a very simple
 * ls implementation.
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void lsd(char *path){
	DIR *dirp = NULL;
	struct dirent *dent = NULL; 

	dirp = opendir( path );

	while(1){
		dent = readdir(dirp);
		if( dent == NULL ) break;

		if( dent->d_name[0] != '.' ){
			printf("%s\n", dent->d_name);
		}
	}	
	
	closedir(dirp);
}

int main(int argc, char **argv){

	struct stat st;

	if( argc == 1 ){
		lsd( "." );
	} else if ( argc == 2 ){
		stat( argv[1], &st );

		if( S_ISDIR(st.st_mode) ){
			lsd( argv[1] );
		} else {
			printf("%d\t%s\n", st.st_size, argv[1]);
		}
	}

	return 0;
}
