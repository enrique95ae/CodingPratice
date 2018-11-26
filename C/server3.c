/*
 Web Server.
 
 Base code: provided by instructor.
 Modified and completed: Enrique Alonso Esposito
 Date: May 7th 2018
 Class: CS436 (Intro to Networking)
 Instructor: Professor Springer.
 
 Programmed in C.
 
 
 Purpose: to create a simple Web server capable of processing one request.
 The server will:
 1. Create a connection socket when contacted by the browser.
 2. Receive the HTTP request form the connection.
 3. Parse the request to determine the specific file being requested.
 4. Get the requeste3d file from the server's file system.
 5. Create an HTTP response message consisting of the requested file preceded by header lines.
 6. Send the response over the TCP connection to the requesting browser.
 
 ----------------------------------------------------
 ----------------------------------------------------
 |                                                  |
 |             HOW TO USE IT:                       |
 |                                                  |
 ----------------------------------------------------
 ----------------------------------------------------
 |
 |  Modify the global variable "fileName"
 |  in order to fix testing files. fileName is located
 |  in line 58. I used a picture (.png) for testing,
 |  any file should work.
 |
 |
 |
 |
 ----------------------------------------------------
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

//DEFINES:
#define MAXLINE 256
#define bufferBytes 1024



//GLOBAL VARIABLES:

const int backlog = 4;
struct sockaddr_in c_addr;

char fileName[] = "Networking.png"

//FUNTION PROTOTYPES:
void *client_request(void *arg);

int main(int argc, char *argv[])
{
    int listenfd;
    int connfd;
    pid_t   childpid;
    int clilen;
    struct  sockaddr_in servaddr;
    char sendBuffer[2000];
    int num;
    pthread_t tid; //Holds the thread's id number
    
    //Arguments checking.
    if (argc != 3) {
        printf("Usage: tcpserver <address> <port> \n");
        return EXIT_FAILURE;
    }
    
    //Retrieving socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Socket checking
    if (listenfd == -1) {
        perror("socket error");
        return EXIT_FAILURE;
    }else{
        printf("socket success");
    }
    
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family        = AF_INET;
    servaddr.sin_addr.s_addr   = inet_addr(argv[1]);
    servaddr.sin_port          = htons(atoi(argv[2]));
    
    //Binding address and port.
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind error");
        return EXIT_FAILURE;
        
    }
    
    //Initialize listen.
    if (listen(listenfd, backlog) == -1) {
        perror("listen error");
        return EXIT_FAILURE;
    }
    
    //Perpetually listening until connection request is received.
    while (1) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0 )
        {
            if (errno == EINTR)
                continue;
            else {
                perror("aceppt error");
                return EXIT_FAILURE;
            }
        }
        
        pthread_create(&tid, NULL, client_request, (void *)&connfd);
    }
    
    close(connfd);
    return 0;
}

void *client_request(void *arg)
{
    int n;
    int connfd;
    connfd = *(int *)arg;
    char fileBuffer[bufferBytes];
    
    write(connfd, fileName, MAXLINE);
    
    //opening the file to be sent
    FILE *file = fopen(fileName, "r");
    //checking if the file could be open.
    if(file == NULL)
    {
        perror("Error Opening the file");
        return EXIT_FAILURE;
    }
    
    while (1) {
        fileBuffer = {0};
        n = fread(fileBuffer, 1, bufferBytes, file);
        
        if
        
        
        if(n > 0)
        {
            write(connfd, fileBuffer, strlen(fileBuffer))
        }
    }
    close(connfd);
}




