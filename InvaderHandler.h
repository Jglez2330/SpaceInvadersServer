//
// Created by jose on 11/04/19.
//

#ifndef SPACEINVADERS_INVADERHANDLER_H
#define SPACEINVADERS_INVADERHANDLER_H

#include "linkedList.h"

typedef struct InvaderHandler{
    Node* invaderList;
    unsigned int IDcounter;


}InvaderHandler;

InvaderHandler* createHandler();

void newEnemies(InvaderHandler* handler);


#endif //SPACEINVADERS_INVADERHANDLER_H
