/*
 * pthreads.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *dostuff(void *);

#ifndef NTHREADS
#define NTHREADS 2
#endif

int main(){

    pthread_t tarry[NTHREADS];
    int status = 0;

    int i = 0;

    for( i = 0; i < NTHREADS; i++ ){
        status = pthread_create( &tarry[i], NULL, dostuff, (void *)&i );
    }

    if(status != 0){
        perror("Failed to create thread");
        exit(EXIT_FAILURE);
    }
    
    for( i = 0; i < NTHREADS; i++ ){
        pthread_join( tarry[i], NULL );
    }

    return 0;
}

void *dostuff(void *arg){
    int i = 0;
    int id = *(int *)arg;
    for( i = 0; i < 5; i++ ){
        printf("Hello, from inside thread %d.\n", id);
        sleep(3);
    }
}
