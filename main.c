#include <stdio.h>
#include <stdlib.h>
#include "Server.h"

int main() {
    printf("Hello, World!\n");


    struct server* server1;
    server1 = (struct server*) malloc(sizeof(struct server));

    aceptarClientes(server1);



    return 0;
}