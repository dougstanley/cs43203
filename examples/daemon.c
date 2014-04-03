/*
 * daemon.c
 *
 * Just a simple example
 * of creating a daemon.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    pid_t p, sid;
    int log_fd;

    p = fork();

    if( p < 0 ){
        perror("Fork Failed!");
        exit(EXIT_FAILURE);
    }else if( p > 0 ){
        /* Have parent exit */
        exit(EXIT_SUCCESS);
    }

    /* Adjust umask, so that logfiles
     * are readable by anyone.
     */
    umask(022);

    /*
     * Open log files here
     * Redirect stderr and stdout
     * to log file
     */

    /* For now, open /dev/null for writing */
    log_fd = open("/dev/null", O_WRONLY);

    /* Redirect STDERR to log */
    /* see dup() */
    close(STDERR_FILENO);
    dup(log_fd);

    close(STDOUT_FILENO);
    dup(log_fd);

    /* Close STDIN last, as we won't need it */
    close(STDIN_FILENO);

    /* Create new session and become session
     * and process group leader
     */
    sid = setsid();
    if( sid < 0 ){
        perror("Setsid failed");
        exit(EXIT_FAILURE);
    }

    /* Change our working directory to
     * a directory that should always exist.
     * '/' is a good example.
     */
    if ((chdir("/")) < 0) {
        perror("Failed to chdir to /");
        exit(EXIT_FAILURE);
    }

    /* Get our pid and write it to a file */
    p = getpid();
    /* still need to write it to a file.. */

    /* Now we do the main work that our
     * daemon is meant to do. For this
     * example, it just sleeps
     */
    while(1){
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}
