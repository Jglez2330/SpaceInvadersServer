//
// Created by Joseph González Pastora on 2019-04-03.
//

#include <stdlib.h>
#include <arpa/inet.h>
#include <memory.h>
#include "Server.h"
#include "JSON/JsonHandler.h"


int serverIniciado = 0;
char*  PORT = "5555";
int maximoClientes = 5;
char buff[4096];
int opt = 1;
struct server* serverStruct = NULL;
char *message = "ECHO Daemon v1.0 \r\n";


/**
 * Inicia el servidor
 * @param structServer ptr of strucServer
 * @return structServer iniciado
 */
struct server* iniciarServer(struct server*  structServer){


    if (structServer == NULL){
        structServer = malloc(sizeof(struct server));
    }


    //Agrega los datos faltantes en la estructura
    structServer->socket = (struct socket *) malloc(sizeof(struct socket));
    structServer->serverSocketMaster = socket(AF_INET, SOCK_STREAM, 0);
    structServer->cantClients = maximoClientes;

    if (structServer->serverSocketMaster < 0){
        error("Error al abrir el socket");
    }

    //Puerto del socket
    structServer->portNumber = atoi(PORT);


    //Setea el socket a multiclientes
    if( setsockopt(structServer->serverSocketMaster, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }


    //Asigna las espcificaciones del socket server
    structServer->socket->serverAddress.sin_family = AF_INET;
    structServer->socket->serverAddress.sin_addr.s_addr = INADDR_ANY;
    structServer->socket->serverAddress.sin_port = htons(structServer->portNumber);


    //Fuerza la union del socket a la tarjeta de red
    bind(structServer->serverSocketMaster, (struct sockaddr*) &structServer->socket->serverAddress,
         sizeof(structServer->socket->serverAddress));

    //Crea un array de clientes
    structServer->clients = (int*) malloc(sizeof(int)*maximoClientes);


    for (int i = 0; i < structServer->cantClients; i++) {

        structServer->clients[i] = 0;
        
    }



    serverIniciado = 1;
    return structServer;
}
/**
 *
 * @param structServer struct del server
 */
void aceptarClientes(struct server* structServer){


    if (serverIniciado) {
        listen(structServer->serverSocketMaster, 5);
        structServer->socket->clientLenght = sizeof(structServer->socket->clientAddress);



        int activity;
        int new_socket;
        int valread;
        Cliente* cliente = malloc(sizeof(Cliente));

        while(1){
            FD_ZERO(&structServer->readfds);

            FD_SET(structServer->serverSocketMaster, &structServer->readfds);
            structServer->max_sd = structServer->serverSocketMaster;

            for ( int i = 0 ; i < maximoClientes ; i++)
            {
                structServer->sd = structServer->clients[i];

                if(structServer->sd > 0)
                    FD_SET( structServer->sd , &structServer->readfds);

                if(structServer->sd > structServer->max_sd)
                    structServer->max_sd = structServer->sd;
            }

            activity = select( structServer->max_sd + 1 , &structServer->readfds , NULL , NULL , NULL);

            if ((activity < 0) && (errno!=EINTR))
            {
                printf("select error");
            }

            if (FD_ISSET(structServer->serverSocketMaster, &structServer->readfds))
            {
                if ((new_socket = accept(structServer->serverSocketMaster,
                                         (struct sockaddr *)&structServer->socket->serverAddress, (socklen_t*)&structServer->socket->clientLenght))<0)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(structServer->socket->serverAddress.sin_addr) , ntohs
                        (structServer->socket->serverAddress.sin_port));

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

            for (int i = 0; i < maximoClientes; i++)
            {
                structServer->sd = structServer->clients[i];

                if (FD_ISSET( structServer->sd , &structServer->readfds))
                {
                    if ((valread = read( structServer->sd , buff, 4095)) == 0)
                    {
                        getpeername(structServer->sd , (struct sockaddr*)&structServer->socket->serverAddress , \
                        (socklen_t*)&structServer->socket->clientLenght);
                        printf("Host disconnected , ip %s , port %d \n" ,
                               inet_ntoa(structServer->socket->serverAddress.sin_addr) , ntohs(structServer->socket->serverAddress.sin_port));

                        close( structServer->sd );
                        structServer->clients[i] = 0;
                    }


                    else
                    {
                        buff[valread] = '\0';
                        printf("%s",buff);

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
/**
 * Imprime el error
 * @param string Tipo de error
 */
void error(char* string) {
    perror(string);
    exit(1);
}

/**
 * Envia un json a todos los clientes observando
 * @param json
 */
void sendAll(cJSON* json){

    if (serverStruct != NULL) {
        for (int i = 0; i < maximoClientes; i++) {
            int cliente = serverStruct->clients[i];

            send(cliente,cJSON_Print(json),strlen(cJSON_Print(json)), 0);

        }
    }

}
