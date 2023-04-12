/**
 * @file        udp.cpp
 * @author      Veronika Jirmusova, xjirmu00
 * @brief       UCP connection
 * @version     0.1
 * @date        2023-03-18
 * 
 * @copyright   Copyright (c) 2023
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
#include <iostream>
#include <unistd.h>
using namespace std;
#define BUFSIZE 1024

/**
 * @brief   Move bytes in buffer when sending message
 * 
 * @param   buffer      buffer with data
 */
void iLikeToMoveItMoveIt(char *buffer){
    size_t len = strlen(buffer);
    for (int i = BUFSIZE - 1; i > 1; i--) {
        buffer[i] = buffer[i - 2];
    }
    buffer[0] = 0;
    buffer[1] = len;
}

/**
 * @brief   Move bytes in buffer when receiving message
 * 
 * @param   buffer      buffer with data
 */
void iCannotMoveItAnymore(char *buffer){
    int tmp = buffer[1];
    int len = buffer[2];
    if(buffer[0] == 1){
        for(int i = 0; i < len; i++){
            buffer[i] = buffer[i+3];
        }
        buffer[len+1] = 0;
        if(tmp == 0){
            printf("OK:%s\n", buffer);
        }else{
            printf("ERR:%s\n", buffer);
        }
    } 
}

/**
 * @brief   Main UDP function
 * 
 * @param   port_number         Number of wanted port
 * @param   server_hostname     Name of server
 * @return  int 
 */
int udp (int port_number, char *server_hostname) {
	int client_socket, bytestx, bytesrx;
    socklen_t serverlen;
    struct hostent *server;
    struct sockaddr_in server_address;
    char buf[BUFSIZE];
    
    //Using DNS to get the adress
    if((server = gethostbyname(server_hostname)) == NULL){
        fprintf(stderr,"ERROR: no such host as %s\n", server_hostname);
        exit(EXIT_FAILURE);
    }
    
    //Find an IP adress of the server
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(port_number);
    
    //Print info about server socket
    //printf("INFO: Server socket: %s : %d \n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
    
    //Make a socket
	if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
	{
		perror("ERROR: socket");
		exit(EXIT_FAILURE);
	}


    //Load an user message
    while(true){
        bzero(buf, BUFSIZE);

        if(fgets(buf, BUFSIZE, stdin) == NULL){
            // If EOF is reached, break out of the loop
            if(feof(stdin)){
                break;
            }
            else{
                perror("ERROR: fgets");
                return 1;
            }
        }
    int len = strlen(buf);
        //Send a message to server
        serverlen = sizeof(server_address);
        iLikeToMoveItMoveIt(buf);
        bytestx = sendto(client_socket, buf, len + 2, 0, (struct sockaddr *) &server_address, serverlen);
        if (bytestx < 0) 
            perror("ERROR: sendto");
        
        //Receiving message from server
        bytesrx = recvfrom(client_socket, buf, BUFSIZE, 0, (struct sockaddr *) &server_address, &serverlen);
        if (bytesrx < 0) 
            perror("ERROR: recvfrom");
        iCannotMoveItAnymore(buf);

    }
    close(client_socket);
    return 0;
}
//End Of File udp.cpp