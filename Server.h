//
// Created by Joseph González Pastora on 2019-04-03.
//

#ifndef SPACEINVADERSSERVER_SERVER_H
#define SPACEINVADERSSERVER_SERVER_H


#include "Socket.h"



struct server{
    struct socket* socket;

    int serverSocketMaster;
    int portNumber;
    int cantClients;

    int max_sd;

    int sd;


    int* clients;

    fd_set readfds;


};

void error(char *string);
void iniciarServer(struct server*  structServer);
void aceptarClientes(struct server* structServer);


#endif //SPACEINVADERSSERVER_SERVER_H
