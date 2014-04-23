/* udp_printer.c
 *
 * Listens on a udp port for messages
 * and for every message it receives,
 * it prints the message to stdout.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

/* Maximum length of bufferr to read/write */
#define MAX_BUFF 4096

/* port we're going to listen on */
#define PORT 1337

int main(int argc, char **argv){
    int sockfd, connfd = 0;
    struct sockaddr_in my_addr;
    socklen_t sin_size;

    char buff[MAX_BUFF];
    int nbytes = 0;
    int ret = 0;

    memset( &my_addr, 0, sizeof(struct sockaddr_in) );
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(PORT);


    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    ret = bind(sockfd, (const struct sockaddr *)&my_addr, sizeof(my_addr)); 
    if( ret != 0 ){
        perror("BIND FAILED!!!!1!!!1!one!11!");
        exit(EXIT_FAILURE);
    }

    while(1){

        nbytes = recvfrom(sockfd, buff, MAX_BUFF, 0, NULL, NULL);

        fwrite(buff,1,nbytes,stdout);

    }

    close(sockfd);
    exit(EXIT_SUCCESS);

    return 0;
}
