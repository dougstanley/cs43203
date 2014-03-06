/*
 * fork.c
 *
 * Just some simple examples
 * of fork()
 */

#include <unistd.h>
#include <stdio.h>

int main(){
	pid_t p;
	int i;

	p = fork();	

	printf("Hello\n");

	if( p != 0 ){
		printf("We\'re waiting...\n");
		wait(NULL);
	}else{
		for( i = 0; i < 5; i++ ){
			printf("I\'m the child still running\n");
			sleep(5);
		}
	}

	printf("Done %d\n",p);	

	return 0;
}
