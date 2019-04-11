#include "invader.h"

//
// Created by jose on 08/04/19.
//
Invader* createInvader(Invader* alien, char tipo, int posX, int posY, int ID){
    alien->tipo = tipo;
    alien->posX = posX;
    alien->posY = posY;
    alien->ID = ID;
    if(tipo == 'a'){
        alien->puntos = 10;
        alien->vida = 1;
    }else if(tipo == 'b'){
        alien->puntos = 20;
        alien->vida = 2;
    }else{
        alien->puntos = 40;
        alien->vida = 3;
    }
    return alien;
}
