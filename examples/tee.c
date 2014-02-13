/*********************
 * tee.c
 *
 * primitive attempt at mimicking
 * the unix tee program.
 *
 * Author: Doug <dmstanle@kent.edu>
 *
 *************************************/
#include <stdio.h>
#include <unistd.h> //for read/write

#define TEE_BUFF_SIZE 4096

int main(int argc, char **argv){
	

	unsigned char buff[TEE_BUFF_SIZE];
	size_t numread, numwrote = 1;
	FILE * out = NULL;
	
	if ( argc > 1 ){
		out = fopen(argv[1], "w");
	} else {
		printf("Please give a filename!\n");
		return 1;
	}

	while( numread > 0 ){
		numread = read(STDIN_FILENO, buff, TEE_BUFF_SIZE);
		numwrote = write(STDOUT_FILENO, buff, numread);	
		numwrote = fwrite(buff, sizeof(unsigned char), numread, out);
	}


	fclose( out );
	
	return 0;
}
