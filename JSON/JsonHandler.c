//
// Created by Joseph González Pastora on 2019-04-12.
//

#include "JsonHandler.h"
#include "../Logica/ComprobarLogica.h"

/**
 * MAneja los json de entrada
 * @param json JSon que el cliente envio
 * @param cliente struct que tiene informacion del cliente
 */
void JSONRequestHandler(cJSON* json, Cliente* cliente){

    //Obtiene el valor del
    int opcodeJSON = cJSON_GetObjectItem(json,"opcode")->valueint;

    //Solo los opcode del cliente juegador entran los demas son de observer, por que no son 0 y 10000 los multiplica
    int opcode = opcodeJSON*cliente->tipoCliente;

    //Responde segun el opcode
    switch (opcode){
        case 0:
            printf("Hola");
            sendAll(json);
            break;

        default:
            break;
    }


}