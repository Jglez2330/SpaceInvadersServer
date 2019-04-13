//
// Created by Fabricio on 9/4/2019.
//

#include "nave.h"

//Función que mueve la nave a la derecha
void NaveAvanzaDer(Nave *nave){
    nave->x1 += nave->vx;
    nave->x2 += nave->vx;
    nave->x3 += nave->vx;
}

//Función que mueve la nave a la izquierda
void NaveAvanzaIzq(Nave *nave){
    nave->x1 -= nave->vx;
    nave->x2 -= nave->vx;
    nave->x3 -= nave->vx;
}

//Función que dispara los misiles de la nave
void NaveDispara(Nave *nave)
{
    if(nave->misiles == NULL){
        nave->misiles = (Misil *) SDL_malloc(sizeof(Misil));
        nave->misiles->x1 = nave->x1;
        nave->misiles->y1 = nave->y1;
        nave->misiles->x2 = nave->x1;
        nave->misiles->y2 = nave->y1 - MISIL_LEN;
        nave->misiles->vy = -MISIL_VEL;
        nave->misiles->siguiente = NULL;
    }
    else{
        Misil *nuevoMisil = nave->misiles;
        while(nuevoMisil->siguiente != NULL){
            nuevoMisil = nuevoMisil->siguiente;
        }
        nuevoMisil->siguiente = (Misil *) SDL_malloc(sizeof(Misil));
        nuevoMisil = nuevoMisil->siguiente;
        nuevoMisil->x1 = nave->x1;
        nuevoMisil->y1 = nave->y1;
        nuevoMisil->x2 = nave->x1;
        nuevoMisil->y2 = nave->y1 - MISIL_LEN;
        nuevoMisil->vy = -MISIL_VEL;
        nuevoMisil->siguiente = NULL;
    }
}

void DibujarNave_Misiles(Nave *nave, SDL_Renderer *renderer)
{
    //Dibujar Misiles
    Misil *nuevoMisil = nave->misiles;
    while(nuevoMisil != NULL){
        MisilAvanza(nuevoMisil);
        SDL_RenderDrawLine(renderer,nuevoMisil->x1,nuevoMisil->y1,nuevoMisil->x2,nuevoMisil->y2);
        nuevoMisil = nuevoMisil->siguiente;
    }

    //DibujarNave
    SDL_Point points[4] = {
            {nave->x1, nave->y1},
            {nave->x2, nave->y2},
            {nave->x3, nave->y3}
    };
    points[3] = points[0];
    SDL_RenderDrawLines(renderer,points,4);
}
