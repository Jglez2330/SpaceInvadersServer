//
// Created by Joseph González Pastora on 2019-04-12.
//

#include "JsonHandler.h"

void JSONRequestHandler(cJSON* json, Cliente* cliente){
    int opcodeJSON = cJSON_GetObjectItem(json,"opcode")->valueint;
    int opcode = opcodeJSON + cliente->tipoCliente*10000;

    switch (opcode){
        case 0:
            printf("Hola");
            //sendAll(json);

            break;
    }


}