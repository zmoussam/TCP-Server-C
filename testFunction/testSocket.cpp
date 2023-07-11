/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:01:55 by zmoussam          #+#    #+#             */
/*   Updated: 2023/07/11 23:11:31 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#define PORT 8000
int main()
{
    int _clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::cout << "the socket descriptor is : " << _clientSocket << std::endl;
    struct sockaddr_in sockAddress;

    memset(&sockAddress, 0, sizeof(sockAddress));
    sockAddress.sin_family = AF_INET; // Define the used domain
    sockAddress.sin_port = htons(PORT);
    sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(_clientSocket, (struct sockaddr *)&sockAddress, sizeof(sockAddress));
    char buffer[10];
    if (read(_clientSocket, buffer, 1) < 0)
        std::cout << "error !" << std::endl;
    std::cout << buffer << std::endl;
    close(_clientSocket);
}