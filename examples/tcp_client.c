/* tcp_client.c
 *
 * a simple example of a tcp
 * client. It connects to our
 * echo server, sends a string,
 * then reads data back from the
 * socket and prints it out.
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

#define PORT 1337

#define MAX_BUFF 1024

int main(int argc, char **argv){
    int sockfd = 0;
    struct sockaddr_in my_addr;
    socklen_t sin_size;

    char buff[MAX_BUFF] = {0};
    int nbytes = 0;
    int ret = 0;

    memset( &my_addr, 0, sizeof(struct sockaddr_in) );
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_addr.sin_port = htons(PORT);


    sockfd = socket(AF_INET,SOCK_STREAM,0);

    ret = connect( sockfd, (const struct sockaddr *)&my_addr, sizeof(my_addr) );
    if( ret != 0 ){
        perror("CONNECT FAILED!!!! OMG!!");
        exit(EXIT_FAILURE);
    }

    nbytes = send(sockfd, "Test!\n", 6, 0); 
    

    nbytes = recv(sockfd, buff, MAX_BUFF, 0);
    fwrite(buff, 1, nbytes, stdout);

    close(sockfd);

    return 0;
}
