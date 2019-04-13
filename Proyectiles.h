//
// Created by Joseph González Pastora on 2019-04-11.
//

#ifndef SPACEINVADERSSERVER_PROYECTILES_H
#define SPACEINVADERSSERVER_PROYECTILES_H

#include "invader.h"
#include <stdlib.h>
#include <stdbool.h>



typedef struct proyectil{
    int posX;
    int posY;


    int velocidad;
}Proyectil;

Proyectil* crearProyectil();
int hayColision(Proyectil* proyectil,Invader invader);
#endif //SPACEINVADERSSERVER_PROYECTILES_H
