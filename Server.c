//
// Created by Joseph González Pastora on 2019-04-03.
//

#include <stdlib.h>
#include <arpa/inet.h>
#include <memory.h>
#include "Server.h"
#include "JSON/JsonHandler.h"


int obseverConectado = 0;
int serverIniciado = 0;
char*  PORT = "5555";
int maximoClientes = 5;
char buff[4096];
int opt = 1;
struct server* serverStruct = NULL;
char *message = "ECHO Daemon v1.0 \r\n";

struct server* iniciarServer(struct server*  structServer){

    structServer->socket = (struct socket *) malloc(sizeof(struct socket));
    structServer->serverSocketMaster = socket(AF_INET, SOCK_STREAM, 0);
    structServer->cantClients = maximoClientes;

    if (structServer->serverSocketMaster < 0){
        error("Error al abrir el socket");
    }

    structServer->portNumber = atoi(PORT);


    if( setsockopt(structServer->serverSocketMaster, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }


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
    return structServer;
}

void aceptarClientes(struct server* structServer){


    if (serverIniciado) {
        listen(structServer->serverSocketMaster, 5);
        structServer->socket->clientLenght = sizeof(structServer->socket->clientAddress);



        int activity;
        int new_socket;
        int valread;

        while(1){
            //clear the socket set
            FD_ZERO(&structServer->readfds);

            //add master socket to set
            FD_SET(structServer->serverSocketMaster, &structServer->readfds);
            structServer->max_sd = structServer->serverSocketMaster;

            //add child sockets to set
            for ( int i = 0 ; i < maximoClientes ; i++)
            {
                //socket descriptor
                structServer->sd = structServer->clients[i];

                //if valid socket descriptor then add to read list
                if(structServer->sd > 0)
                    FD_SET( structServer->sd , &structServer->readfds);

                //highest file descriptor number, need it for the select function
                if(structServer->sd > structServer->max_sd)
                    structServer->max_sd = structServer->sd;
            }

            //wait for an activity on one of the sockets , timeout is NULL ,
            //so wait indefinitely
            activity = select( structServer->max_sd + 1 , &structServer->readfds , NULL , NULL , NULL);

            if ((activity < 0) && (errno!=EINTR))
            {
                printf("select error");
            }

            //If something happened on the master socket ,
            //then its an incoming connection
            if (FD_ISSET(structServer->serverSocketMaster, &structServer->readfds))
            {
                if ((new_socket = accept(structServer->serverSocketMaster,
                                         (struct sockaddr *)&structServer->socket->serverAddress, (socklen_t*)&structServer->socket->clientLenght))<0)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                //inform user of socket number - used in send and receive commands
                printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(structServer->socket->serverAddress.sin_addr) , ntohs
                        (structServer->socket->serverAddress.sin_port));

                //send new connection greeting message
                if( send(new_socket, message, strlen(message), 0) != strlen(message) )
                {
                    perror("send");
                }

                puts("Welcome message sent successfully");

                //add new socket to array of sockets
                for (int i = 0; i < maximoClientes; i++)
                {
                    //if position is empty
                    if( structServer->clients[i] == 0 )
                    {
                        structServer->clients[i] = new_socket;
                        printf("Adding to list of sockets as %d\n" , i);

                        break;
                    }
                }
            }

            //else its some IO operation on some other socket
            for (int i = 0; i < maximoClientes; i++)
            {
                structServer->sd = structServer->clients[i];

                if (FD_ISSET( structServer->sd , &structServer->readfds))
                {
                    //Check if it was for closing , and also read the
                    //incoming message
                    if ((valread = read( structServer->sd , buff, 4095)) == 0)
                    {
                        //Somebody disconnected , get his details and print
                        getpeername(structServer->sd , (struct sockaddr*)&structServer->socket->serverAddress , \
                        (socklen_t*)&structServer->socket->clientLenght);
                        printf("Host disconnected , ip %s , port %d \n" ,
                               inet_ntoa(structServer->socket->serverAddress.sin_addr) , ntohs(structServer->socket->serverAddress.sin_port));

                        //Close the socket and mark as 0 in list for reuse
                        close( structServer->sd );
                        structServer->clients[i] = 0;
                    }

                        //Echo back the message that came in
                    else
                    {
                        //set the string terminating NULL byte on the end
                        //of the data read
                        buff[valread] = '\0';
                        printf("%s",buff);
                        Cliente* cliente = malloc(sizeof(Cliente));

                        cliente->socket = structServer->sd;
                        cliente->tipoCliente = i;
                        cliente->serverSocket = structServer->serverSocketMaster;
                        JSONRequestHandler(cJSON_Parse(buff),cliente);
                    }
                }
            }
            serverStruct = structServer;

        }



    } else{
        structServer = iniciarServer(structServer);
        aceptarClientes(structServer);
    }
}

void error(char* string) {
    perror(string);
    exit(1);
}


void sendAll(cJSON* json){

    if (serverStruct != NULL) {
        for (int i = 0; i < maximoClientes; i++) {
            int cliente = serverStruct->clients[i];

            send(cliente,cJSON_Print(json),strlen(cJSON_Print(json)), 0);

        }
    }

}
