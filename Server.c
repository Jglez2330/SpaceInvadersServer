//
// Created by Joseph González Pastora on 2019-04-03.
//

#include <stdlib.h>
#include <arpa/inet.h>
#include <memory.h>
#include "Server.h"


int obseverConectado = 0;
int serverIniciado = 0;
char*  PORT = "5555";
int maximoClientes = 2;

void iniciarServer(struct server*  structServer){

    structServer->socket = (struct socket*) malloc(sizeof(struct socket));
    structServer->serverSocketMaster = socket(AF_INET,SOCK_STREAM,0);

    structServer->cantClients = maximoClientes;

    if (structServer->serverSocketMaster < 0){
        error("Error al abrir el socket");
    }

    structServer->portNumber = atoi(PORT);


    structServer->socket->serverAddress.sin_family = AF_INET;
    structServer->socket->serverAddress.sin_addr.s_addr = INADDR_ANY;
    structServer->socket->serverAddress.sin_port = htons(structServer->portNumber);


    bind(structServer->serverSocketMaster, (struct sockaddr*) &structServer->socket->serverAddress,
         sizeof(structServer->socket->serverAddress));

    structServer->clients = (int*) malloc(sizeof(int)*maximoClientes);


    for (int i = 0; i < structServer->cantClients; i++) {

        structServer->clients[i] = 0;
        
    }



    serverIniciado = 1;
}

void aceptarClientes(struct server* structServer){


    if (serverIniciado) {
        listen(structServer->serverSocketMaster, 5);
        structServer->socket->clientLenght = sizeof(structServer->socket->clientAddress);

        int activity;
        int new_socket;
        int valread;
        while (1) {

            FD_ZERO(&structServer->readfds);
            FD_SET(structServer->serverSocketMaster,&structServer->readfds);

            structServer->max_sd = structServer->serverSocketMaster;

            for (int i = 0; i <  structServer->cantClients; i++) {

                structServer->sd = structServer->clients[i];

                if (structServer->sd > 0){
                    FD_SET(structServer->sd,&structServer->readfds);
                }

                if (structServer->sd > structServer->max_sd){
                    structServer->max_sd = structServer->sd;
                }

            }
            activity = select(structServer->max_sd + 1,
                    &structServer->readfds,
                    NULL,
                    NULL,
                    NULL);


            if (FD_ISSET(structServer->serverSocketMaster, &structServer->readfds)) {

                if ((new_socket = accept(structServer->serverSocketMaster,
                                         (struct sockaddr *) &structServer->socket->serverAddress,
                                         (socklen_t *) &structServer->socket->clientLenght)) < 0) {

                    error("accept");


                }
                printf("New connection , socket fd is %d , ip is : %s , port : %d\n",
                       new_socket,
                       inet_ntoa(structServer->socket->serverAddress.sin_addr),
                       ntohs(structServer->socket->serverAddress.sin_port));


                for (int j = 0; j < structServer->cantClients; j++) {

                    if (structServer->clients[j] == 0) {

                        structServer->clients[j] = new_socket;
                        printf("Adding to list of sockets as %d\n", j);
                        break;

                    }

                }
            }
            for (int k = 0; k < structServer->cantClients; k++) {
                structServer->sd = structServer->clients[k];

                if (FD_ISSET(structServer->sd,&structServer->readfds)){

                    if ( (valread = read(structServer->sd,structServer->socket->buffer,256)) == 0){
                        getpeername(structServer->sd, (struct sockaddr*) &structServer->socket->serverAddress,
                                    (socklen_t*) &structServer->socket->clientLenght);

                        printf("Host disconnected , ip %s , port %d \n" ,
                               inet_ntoa(structServer->socket->serverAddress.sin_addr) , ntohs(structServer->socket->serverAddress.sin_port));

                        close( structServer->sd );
                        structServer->clients[k] = 0;
                    }
                } else{
                    structServer->socket->buffer[valread] = '\0';
                    send(structServer->sd,structServer->socket->buffer,strlen(structServer->socket->buffer),0);
                }
                
            }

            printf("Se conecta el mae");
        }
    } else{
        iniciarServer(structServer);
        aceptarClientes(structServer);
    }
}

void error(char* string) {
    perror(string);
    exit(1);
}

