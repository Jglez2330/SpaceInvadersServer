//
// Created by jose on 11/04/19.
//

#ifndef SPACEINVADERS_INVADERHANDLER_H
#define SPACEINVADERS_INVADERHANDLER_H


#include <SDL_render.h>
#include "linkedList.h"
#include "nave.h"

typedef struct InvaderHandler{
    Node* invaderList;
    unsigned int IDcounter;


}InvaderHandler;

InvaderHandler* createHandler();

void newEnemies(InvaderHandler* handler);

void MoverInvaders(InvaderHandler* handler);

void DispararInvaders(InvaderHandler* handler);

void DibujarInvaders(InvaderHandler* handler,SDL_Renderer *renderer);

void EliminarMisiles(Nave* nave,InvaderHandler* handler);

int EliminarMisilesInvaders(Nave *nave,InvaderHandler* handler);

Node** JtoL(cJSON* json);



#endif //SPACEINVADERS_INVADERHANDLER_H
