/******************************************
 * pipe.c
 *
 * Simple explanation of what
 * happens when you use the
 * | pipe operator in the command
 * shell to join the stdout of
 * one process to stdin of another.
 *
 * This program basically is performing
 * the same task that the shell command:
 *
 * ps -ef | grep dostanle
 *
 * would do.
 *****************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    //array to hold file descriptors
    //created by pipe system call
    int fds[2] = {0};
    
    //Needed to hold process id of
    //forked process.
    int pid;

    //create a pipe as a pair
    //of file descriptors
    pipe(fds);
    
    //spawn a child process
    pid = fork();    

    //if we're pid 0, we're the child.
    if( pid == 0 ){
        /* the child will be running the
         * process on the right hand side
         * of the |, so it needs it's
         * stdin connected to the pipe.   
         */

        
        /* What in the world are we doing here?
         * Well, first, we close standard input,
         * as we aren't going to use it. We want
         * input to come from the pipe.
         *
         * Next, we duplicate the read end of the
         * pipe. dup() copies the file descriptor
         * passed in, and creates a new one using
         * the lowest available number. Well, we
         * just closed 0, and you don't get much
         * lower than that, so 0 gets used.
         *
         * Now, from this point on, any thing that
         * would normally read from standard in,
         * is now reading from the pipe instead.
         */
        close(0);
        dup(fds[0]);

    } else {
        /* Here we do basically exactly the same
         * as above, only we close off standard out
         * and duplicate the write end of the pipe.
         *
         * So basically after this point, anything
         * that would normally write to standard out,
         * will now be writing to the write end of
         * the pipe instead.
         */
        close(1);
        dup(fds[1]);
    }


    /* Now that we have pipe ends hooked up
     * where standard input/output normally
     * would be, we can spawn two new processes,
     * and they will inherit the file descriptors
     * we currently have set up (including our
     * changed descriptors for stdin/stdout).
     */
    if( pid != 0 ){
        /* If the process id is not 0, then
         * we're the parent process, so we'll
         * run the command on the left hand side
         * of the |.
         *
         * Any output that would have normally been
         * written to standard out, is now being
         * written to the write end of the pipe.
         */
        system("ps -ef");
    } else {
        /* If we're not the parent, we must be
         * the child. So we run the command from
         * the right hand side of the |.
         *
         * Anything that would normall read from
         * it's standard input is now reading from
         * the read end of the pipe, i.e. it reads
         * in what the other process is writing out.
         */
        system("grep dostanle");
    }
}
