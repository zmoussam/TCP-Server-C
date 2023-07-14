/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:07:57 by zmoussam          #+#    #+#             */
/*   Updated: 2023/07/14 21:50:03 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TRUE 1
#define FALSEE 0
#define BUFFER_SIZE 50

int main()
{
    int serverSocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket_fd != -1)
    {
        //
    }
    else 
    {
        printf("Error in socket Function, Line 37\n");
    }

    int option = TRUE;
    setsockopt(serverSocket_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&option, sizeof(option));

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(4444);

    if(bind(serverSocket_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == 0)
        printf("Server is binded to port no. 4444\n");
    else
        return(printf("Error in bind() Function , line 53\n"));
    if (listen(serverSocket_fd, 4) == 0)
        printf("listenning ... \n");
    else 
        return(printf("Errot in listen() Function , line 65\n"));
    
    struct sockaddr_in connectionClientAddress;
    int clientAddrLength = 0;
    while(1)
    {
        memest(&connectionClientAddress, 0, sizeof(connectionClientAddress));
        int connectionServerSock_fd = accept(serverSocket_fd, (struct sockaddr *)&connectionClientAddress, &clientAddrLength);

        if (connectionServerSock_fd == -1)
        {
            printf("Error in accept() Function, Line 82\n");
            continue;
        }
        else 
            printf("New client with is connected\n");

        pid_t pid = fork();
        if (pid == -1)
        {
            close(connectionServerSock_fd);
            continue;
        }
        if (pid == 0)
        {
            close(serverSocket_fd);
            char buffer[BUFFER_SIZE];
            while (1)
            {
                memset(buffer, 0, BUFFER_SIZE);
                recv(connectionServerSock_fd, buffer, BUFFER_SIZE, 0);
                printf("%s\n", buffer);
                if (buffer[0] == 'q' || buffer[0] == 'Q')
                {
                    printf("Client is disconnected\n");
                    close(connectionServerSock_fd);
                    exit(27);
                }
                else 
                    send(connectionServerSock_fd, buffer, strlen(buffer), 0);
            }
            
        }
        else 
            close(connectionServerSock_fd);
    }
}