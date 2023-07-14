/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_client.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:35:19 by zmoussam          #+#    #+#             */
/*   Updated: 2023/07/14 16:19:25 by zmoussam         ###   ########.fr       */
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

#define SERVER_IP "127.0.0.1"
#define PORT 8000

int main()
{
    // 1. create a socket for the client.
    int _clientSocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_clientSocket_fd != -1)
        printf("Client Socket ID: %d\n", _clientSocket_fd);
    else 
        return(printf("Failed to create a socket. \n"));

    //2. connect the client to a specific server
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0 ,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddress.sin_port = htons(PORT);

    if (connect(_clientSocket_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == 0)
        printf("Connected successfully.\n");
    else
        return(printf("Faild to connect.\n"));


    //3. send data to the server
    char buffer[1024] = "Hello, i am Zakaria\n";

    send(_clientSocket_fd, buffer, strlen(buffer), 0);

    //4. receieve data from the server
    memset(buffer, 0, 1024);
    recv(_clientSocket_fd, buffer, 1024, 0);
    printf("%s\n", buffer);
    close(_clientSocket_fd);
}