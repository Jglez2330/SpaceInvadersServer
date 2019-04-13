//
// Created by jose on 08/04/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H


#include <SDL_render.h>
#include "misil.h"
#include "JSON/cJSON.h"

#define MISIL_LEN 5
#define MISIL_VEL 10


typedef struct Invader{
    char* tipo; //'a' calamar, 'b' cangrejo, 'c' pulpo
    int vida, puntos;
    int ID;
    int x1,y1;
    int x2,y2;
    int x3,y3;

    Misil *misiles;
}Invader;

Invader* createInvader(char* tipo, int posX, int posY,int ID);

void InvaderAvanza(Invader* invader);

void InvaderDispara(Invader* invader);

void DibujarInvader_Misiles(Invader* invader, SDL_Renderer *renderer);

cJSON* ItoJ(Invader* invader);
Invader* JtoIL(cJSON* json);


#endif //SPACEINVADERS_INVADER_H
