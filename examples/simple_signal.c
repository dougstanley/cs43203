/****************************
 * simple_signal.c
 *
 * This is an extremely simple
 * example of using signal handlers.
 *
 * It basically registers a handler
 * to catch the SIGINT signal (what
 * is sent when you press <CTRL>-C)
 * and instead of stopping the program
 * like it normally would, it instead
 * asks the user if they would like to
 * quit.
 *
 * We also register another handler
 * listening for the SIGUSR1 signal
 * and print out a message that we
 * received the signal, then we go
 * back about our business. The USR1
 * signal can be sent to our process
 * from another process using the kill
 * command or the kill() system call,
 * as long as the other process knows
 * our process id number.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/* Simple function prompts user if she
 * would like to quit, and exits the
 * program if she indicates Y or y.
 */
void prompt(int sig){
    char answer = 0;
    printf("Would you like to exit? Y/N");
    scanf("%c", &answer);
    if(answer == 'Y' || answer == 'y') exit(0);
    else return;
}

/* Another simple example of a simple
 * signal handler which just prints
 * a message.
 */
void user(int sig){
    printf("User sent us a signal: %d\n", sig);
}

int main(int argc, char *argv[]){
    /* These structs hold all the info
     * needed for setting up a signal
     * handler
     */
    struct sigaction mysig;
    struct sigaction usersig;

    /* This holds a set of signals that
     * need to be ignored. 
     */ 
    sigset_t mymask;
    
    /* Here we fill the mask set in with
     * a list of all the signals. We
     * fill it with all the signals, because
     * we're using this list to ignore signals
     * while our code is running the signal
     * handler function. It doesn't make sense
     * for our signal handler to quit because
     * it too received a signal.
     */
    sigfillset( &mymask );

    /* Assign the andler and mask to
     * our sigaction struct.
     */
    mysig.sa_handler = &prompt; 
    mysig.sa_mask = mymask;

    /* Assign the handling of SIGINT
     * to the structure we filled above.
     */
    sigaction( SIGINT, &mysig, NULL);

    /* Now we do the same again,
     * only now we register our user
     * function to respond to signals
     * of USR1 type.
     */
    usersig.sa_handler = &user;
    usersig.sa_mask = mymask;
    sigaction( SIGUSR1, &usersig, NULL);

    
    /* Infinite loop while we wait
     * for signals.
     */
    while(1){
        sleep(1);
    }

    return 0;
}
