//
// Created by Joseph González Pastora on 2019-04-11.
//

#include "ObjetosJuego.h"
#include "invader.h"
#include "Proyectiles.h"
#include "Barreras.h"

typedef struct Objeto{
    union{
        Invader* invader;
        Proyectil* proyectil;
        Barrera* barrera;
 //       Jugador* jugador;
    }objeto;

    int type;

    int width;
    int height;
};