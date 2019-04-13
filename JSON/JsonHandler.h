//
// Created by Joseph González Pastora on 2019-04-12.
//

#include "cJSON.h"
#include "../Clientes.h"
#include "../Server.h"

#ifndef SPACEINVADERSSERVER_JSONHANDLER_H
#define SPACEINVADERSSERVER_JSONHANDLER_H

void JSONRequestHandler(cJSON* json,Cliente* cliente);
#endif //SPACEINVADERSSERVER_JSONHANDLER_H
