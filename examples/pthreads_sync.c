/*
 * pthreads.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *dostuff(void *);

#ifndef NTHREADS
#define NTHREADS 4
#endif

pthread_mutex_t gary;

int main(){

    pthread_t tarry[NTHREADS];
    int thread_ids[NTHREADS] = {0};
    int status = 0;

    int i = 0;

    pthread_mutex_init( &gary, NULL );

    for( i = 0; i < NTHREADS; i++ ){
        thread_ids[i] = i;
        status = pthread_create( &tarry[i], NULL, dostuff, (void *)&thread_ids[i] );
    }

    if(status != 0){
        perror("Failed to create thread");
        exit(EXIT_FAILURE);
    }
    
    for( i = 0; i < NTHREADS; i++ ){
        pthread_join( tarry[i], NULL );
    }

    pthread_mutex_destroy( &gary );

    return 0;
}

void *dostuff(void *arg){
    int i = 0;
    int id = *(int *)arg;
    char msg[1024] = {0};
    int len = 0;

    sprintf(msg,"Hello, from inside thread %d.\n", id);
    len = strlen(msg);    

    for( i = 0; i < 5; i++ ){
        pthread_mutex_lock( &gary );
        write(0, msg, len);
        pthread_mutex_unlock( &gary );
    }
}
