/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:34:30 by zmoussam          #+#    #+#             */
/*   Updated: 2023/07/14 17:54:14 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8000
int main()
{
    //1. create a socket for the server

    int _serverSocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket_fd != -1)
        printf("Server Socket ID: %d\n", _serverSocket_fd);
    else
        return(printf("Faile to create a socket.\n"));

    //2. bind this socket to a specific port number

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);

    if (bind(_serverSocket_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == 0)
        printf("Server is binded to port no. 8000\n");
    else
        return(printf("binding Failed\n"));

    //3. listen to the clients connection requests

    if (listen(_serverSocket_fd, 1) == 0)
        printf("listenning ...\n");
    else
        return(printf("Failed to listen\n"));

    //4. accept the connection request

    struct sockaddr_in connectedClientAddtress;
    memset(&connectedClientAddtress, 0, sizeof(connectedClientAddtress));

    int clientAddtLenght = 0;

    int _connectionServerSocket_fd = accept(_serverSocket_fd, (struct sockaddr *)&connectedClientAddtress, (socklen_t *)&clientAddtLenght);

    if (_connectionServerSocket_fd == -1)
        return(printf("Failed to accept a connection request\n"));
    else
        printf("Accept a request at socket ID: %d\n", _connectionServerSocket_fd);

    //5. send or reciever data from the clients

    char recievedMsg[1024];
    recv(_connectionServerSocket_fd, recievedMsg, 1024, 0);
    printf("recieved msg : %s\n", recievedMsg);

    //6. close the socket

    close(_serverSocket_fd);
    close(_connectionServerSocket_fd);
}