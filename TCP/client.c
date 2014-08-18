/*
 * tcpclient.c - A simple TCP client
 * usage: tcpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 1024

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}

//char string[] = "C|AC-2C-3C-BOB";
//char* s;
//char* hand[3];
//char* usr;
//
////void blablabla(void)
////{
////    s = (char*) calloc(1, sizeof(char));
////    hand[0] = (char*) calloc(3, sizeof(char));
////    hand[1] = (char*) calloc(3, sizeof(char));
////    hand[2] = (char*) calloc(3, sizeof(char));
////    usr = (char*) calloc(21, sizeof(char));
////    
////    s = strtok (string,"|");
////    hand[0] = strtok (NULL, "-");
////    hand[1] = strtok (NULL, "-");
////    hand[2] = strtok (NULL, "-");
////    usr = strtok (NULL, "\0");
////    
////    printf("%s:%s:%s:%s:%s\n", s, hand[1], hand[2], hand[3], usr);
////}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname = "192.168.0.110";
    char buf[BUFSIZE];
    
    
    //Parsing
    const char s[2] = "|";
    char *token;
    
    /* check command line arguments */
    //if (argc != 3) {
    //    fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
    //    exit(0);
   // }
    
    printf("test %s",argv[1]);
    //hostname = argv[1]; //192.168.0.110
    portno = 12000;//atoi(argv[2]); //12000
    
    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    
    /* gethostbyname: get the server's DNS entry */
    printf("BLABLABLA");

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);
    
    /* connect: create a connection with the server */
    if (connect(sockfd, &serveraddr, sizeof(serveraddr)) < 0)
        error("ERROR connecting ");
    
    while (1) {
        //SCHRIJVEN MAG AF
    /* get message line from the user */
        for(int i; i<100; i++){
        char toSend[20];
        snprintf(toSend, sizeof(toSend), "%i|%i|%i|%i| \r\n",i,i*2,i*3,i*4);
        
        printf("STRING:[ %s ] \n sockfd = %d\n",toSend, sockfd);
        n = write(sockfd, toSend, strlen(toSend));
        }
//    /* send the message line to the server */
//    n = write(sockfd, buf, strlen(buf));
//    if (n < 0)
//        error("ERROR writing to socket");
    
    /* print the server's reply */
    bzero(buf, BUFSIZE);
    n = read(sockfd, buf, BUFSIZE);
    if (n < 0)
        error("ERROR reading from socket");
        printf("Phil says:  %s \n\r", buf);
        
        token = strtok(buf, s);
        
        /* walk through other tokens */
        while( token != NULL )
        {
            printf( " %s\n", token );
            token = strtok(NULL, s);
        }
    }
    close(sockfd);
    return 0;
}

