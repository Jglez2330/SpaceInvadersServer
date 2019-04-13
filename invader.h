//
// Created by jose on 08/04/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H

typedef struct Invader{
<<<<<<< Updated upstream
    char tipo; //'a' calamar, 'b' cangrejo, 'c' pulpo
    int vida, posX, posY, puntos;
    int ID;
=======
    char tipo; //'a' calamar, 'b' cangrejo, 'c' pulpo 'z' madre no

    int puntos;
    int posY;
    int posX;
    int vida;

>>>>>>> Stashed changes
}Invader;

Invader* createInvader(char tipo, int posX, int posY,int ID);

#endif //SPACEINVADERS_INVADER_H
