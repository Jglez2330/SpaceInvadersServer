//
// Created by jose on 08/04/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H

typedef struct Invader{
    char tipo; //'a' calamar, 'b' cangrejo, 'c' pulpo
    int vida, posX, posY, puntos;
    int ID;
}Invader;

Invader* createInvader(Invader* alien, char tipo, int posX, int posY,int ID);

#endif //SPACEINVADERS_INVADER_H
