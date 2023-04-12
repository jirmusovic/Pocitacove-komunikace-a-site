/**
 * @file        tcp.cpp
 * @author      Veronika Jirmusova, xjirmu00
 * @brief       TCP communication with server
 * @version     0.1
 * @date        2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define BUFSIZE 1024

/**
 * @brief   Main TCP function   
 * 
 * @param   port_number         wanted port number
 * @param   server_hostname     name of server
 * @return int 
 */
int tcp(int port_number, char *server_hostname){
    
    int client_socket, bytestx, bytesrx;
    socklen_t serverlen;
    struct hostent *server;
    struct sockaddr_in server_address;
    char buf[BUFSIZE];

    //Check if the name of wanted server is correct
    if ((server = gethostbyname(server_hostname)) == NULL){
            fprintf(stderr,"ERROR: no such host as %s\n", server_hostname);
            exit(EXIT_FAILURE);
        }
        
        //Find an IP adress of wanted server
        bzero((char *) &server_address, sizeof(server_address));
        server_address.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
        server_address.sin_port = htons(port_number);
        
        //Print info about the server socket
        //printf("INFO: Server socket: %s : %d \n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
        
        //Declaration of socket
        if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
        {
            perror("ERROR: socket");
            exit(EXIT_FAILURE);
        }
        
        ///Get the message from user
        if (connect(client_socket, (const struct sockaddr *) &server_address, sizeof(server_address)) != 0)
        {
            perror("ERROR: connect");
            exit(EXIT_FAILURE);        
        }

    bool bye = false;
    //Established connection
    while(true){
        bzero(buf, BUFSIZE);
        //printf("Please enter msg: ");
        //Send BYE to server if an error is caught
        if(fgets(buf, BUFSIZE, stdin) == NULL){
            strcpy(buf, "BYE\n");
            send(client_socket, buf, strlen(buf), 0);
            recv(client_socket, buf, BUFSIZE, 0);
            break;
        }
            
        //Send a message to server
        bytestx = send(client_socket, buf, strlen(buf), 0);
        if (bytestx < 0) 
            perror("ERROR in sendto");
        
        bzero(buf, BUFSIZE);

        //Receive an answer
        bytesrx = recv(client_socket, buf, BUFSIZE, 0);
        if (bytesrx < 0) 
            perror("ERROR in recvfrom");
        
        printf("%s", buf);

        if(!strcmp(buf, "BYE\n")){
            break;
        }
    }
    close(client_socket);
    return 0;
}
//End Of File tcp.cpp