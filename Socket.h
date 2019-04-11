//
// Created by Joseph González Pastora on 2019-04-03.
//

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#ifndef SPACEINVADERSSERVER_SOCKET_H
#define SPACEINVADERSSERVER_SOCKET_H



struct socket{
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    struct sockaddr_in observerAddress;
    socklen_t clientLenght;

    char buffer[256];

};



#endif //SPACEINVADERSSERVER_SOCKET_H


