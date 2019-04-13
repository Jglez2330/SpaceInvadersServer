//
// Created by Joseph González Pastora on 2019-04-03.
//

#ifndef SPACEINVADERSSERVER_SERVER_H
#define SPACEINVADERSSERVER_SERVER_H


#include "Socket.h"
#include "Clientes.h"
#include "JSON/cJSON.h"
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD



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

//struct server* iniciarServer(struct server*  structServer);
void aceptarClientes(struct server* structServer);

void* escucharCliente(void* cliente);

void sendAll(cJSON* json);


#endif //SPACEINVADERSSERVER_SERVER_H
