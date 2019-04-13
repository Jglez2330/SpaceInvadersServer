//
// Created by Fabricio on 9/4/2019.
//


#ifndef PRUEBAINTERFAZ_NAVE_H
#define PRUEBAINTERFAZ_NAVE_H

#include <SDL_render.h>
#include "misil.h"

#define MISIL_LEN 5
#define MISIL_VEL 7


 typedef struct Nave{
    int x1,y1;
    int x2,y2;
    int x3,y3;
    int vx;
    int vida;
    int puntuacion;
    Misil *misiles;
}Nave;

void DibujarNave_Misiles(Nave *nave, SDL_Renderer *renderer);
void NaveAvanzaDer(Nave *nave);
void NaveAvanzaIzq(Nave *nave);
void NaveDispara(Nave *nave);

#endif //PRUEBAINTERFAZ_NAVE_H
