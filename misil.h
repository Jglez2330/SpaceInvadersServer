//
// Created by Fabricio on 9/4/2019.
//

#ifndef PRUEBAINTERFAZ_MISIL_H
#define PRUEBAINTERFAZ_MISIL_H


#include <SDL_rect.h>
#include "JSON/cJSON.h"

typedef struct Misil{
    int x1,y1;
    int x2,y2;
    int vy;
    struct Misil *siguiente;
}Misil;

void MisilAvanza (Misil *misil);
int colisiones(SDL_Rect *rect1, SDL_Rect *rect2);
SDL_Rect crearRectanguloMisil(Misil *misil);

cJSON* MLtoJ(Misil* misil);

Misil* JtoML(cJSON* misil);
#endif //PRUEBAINTERFAZ_MISIL_H
