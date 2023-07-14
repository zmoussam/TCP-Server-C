/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:07:57 by zmoussam          #+#    #+#             */
/*   Updated: 2023/07/14 22:13:43 by zmoussam         ###   ########.fr       */
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

void Write_Routine(int sock, char *buf);
void Read_Routine(int sock, char *buf);

//void Read_Child_Process(void);

int main()
{
    int clientSocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket_fd != -1)
    {
        printf("client's Socket: %d\n", clientSocket_fd);
    }
    else 
    {
        return(printf("Error in socket Function, Line 37\n"));
    }

    struct sockaddr_in passivServerAddress;
    memset(&passivServerAddress, 0, sizeof(passivServerAddress));

    passivServerAddress.sin_family = AF_INET;
    passivServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    passivServerAddress.sin_port = htons(4444);

    if(connect(clientSocket_fd, (struct sockaddr *)&passivServerAddress, sizeof(passivServerAddress)) != 0)
    {
        printf("Error connect() line : 38\n");
        exit(1);
    }
    else
        printf("Welcome to our echo system.\n");
    
    char buffer[BUFFER_SIZE];

    pid_t pid = fork();
    if (pid == 0)
        Write_Routine(clientSocket_fd, buffer);
    else
        Read_Routine(clientSocket_fd, buffer);
}

void Write_Routine(int sock, char * buf)
{
    while(1)
    {
        scanf("%s", buf);
        send(sock, buf, BUFFER_SIZE, 0);
        if (*buf == 'q' || *buf == 'Q')
        {
            close(sock);
            printf("Client is disconnected\n");
            return;
        }
        memset(buf, 0, BUFFER_SIZE);
    }
}

void Read_Routine(int sock, char * buf)
{
    while(1)
    {
        recv(sock, buf, BUFFER_SIZE, 0);
        if (strlen(buf) <= 0)
        {
            close(sock);
            return ;
        }
        printf("Message from the server: %s\n", buf);
        memset(buf, 0, BUFFER_SIZE);
    }
}