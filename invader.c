#include <stdlib.h>
#include "invader.h"
//
// Created by jose on 08/04/19.
//
Invader* createInvader(char* tipo, int posX, int posY, int ID){
    Invader* alien = malloc(sizeof(Invader));
    alien->tipo = tipo;
    alien->x1 = posX;
    alien->y1 = posY;

    alien->ID = ID;
    alien->misiles = NULL;
    if(*tipo == 'a'){
        alien->puntos = 10;
        alien->vida = 2;
        alien->x2 = posX-20;
        alien->y2 = posY-20;
        alien->x3 = posX+20;
        alien->y3 = posY-20;
    }else if(*tipo == 'b'){
        alien->puntos = 20;
        alien->vida = 3;
        alien->x2 = posX-20;
        alien->y2 = posY-30;
        alien->x3 = posX+20;
        alien->y3 = posY-30;
    }else{
        alien->puntos = 40;
        alien->vida = 4 ;
        alien->x2 = posX-30;
        alien->y2 = posY-20;
        alien->x3 = posX+30;
        alien->y3 = posY-20;
    }
    return alien;
}


void InvaderAvanza(Invader* invader){
    invader->y1 += 7;
    invader->y2 += 7;
    invader->y3 += 7;
}


//Función que dispara los misiles de la nave
void InvaderDispara(Invader* invader)
{
    if(invader->misiles == NULL){
        invader->misiles = (Misil *) SDL_malloc(sizeof(Misil));
        invader->misiles->x1 = invader->x1;
        invader->misiles->y1 = invader->y1;
        invader->misiles->x2 = invader->x1;
        invader->misiles->y2 = invader->y1 - MISIL_LEN;
        invader->misiles->vy = MISIL_VEL;
        invader->misiles->siguiente = NULL;
    }
    else{
        Misil *nuevoMisil = invader->misiles;
        while(nuevoMisil->siguiente != NULL){
            nuevoMisil = nuevoMisil->siguiente;
        }
        nuevoMisil->siguiente = (Misil *) SDL_malloc(sizeof(Misil));
        nuevoMisil = nuevoMisil->siguiente;
        nuevoMisil->x1 = invader->x1;
        nuevoMisil->y1 = invader->y1;
        nuevoMisil->x2 = invader->x1;
        nuevoMisil->y2 = invader->y1 - MISIL_LEN;
        nuevoMisil->vy = MISIL_VEL;
        nuevoMisil->siguiente = NULL;
    }
}

void DibujarInvader_Misiles(Invader* invader, SDL_Renderer *renderer)
{
    //Dibujar Misiles
    Misil *nuevoMisil = invader->misiles;
    while(nuevoMisil != NULL){
        MisilAvanza(nuevoMisil);
        SDL_RenderDrawLine(renderer,nuevoMisil->x1,nuevoMisil->y1,nuevoMisil->x2,nuevoMisil->y2);
        nuevoMisil = nuevoMisil->siguiente;
    }

    //DibujarNave
    SDL_Point points[4] = {
            {invader->x1, invader->y1},
            {invader->x2, invader->y2},
            {invader->x3, invader->y3}
    };
    points[3] = points[0];
    SDL_RenderDrawLines(renderer,points,4);
}

cJSON* ItoJ(Invader* invader){
    cJSON* invaderJSON = cJSON_CreateObject();
    cJSON* tipo = cJSON_CreateString(invader->tipo);
    cJSON* vida = cJSON_CreateNumber(invader->vida);
    cJSON* puntos = cJSON_CreateNumber(invader->puntos);
    cJSON* ID = cJSON_CreateNumber(invader->ID);
    cJSON* x1 = cJSON_CreateNumber(invader->x1);
    cJSON* y1 = cJSON_CreateNumber(invader->y1);
    cJSON* x2 = cJSON_CreateNumber(invader->x2);
    cJSON* y2 = cJSON_CreateNumber(invader->y2);
    cJSON* x3 = cJSON_CreateNumber(invader->x3);
    cJSON* y3 = cJSON_CreateNumber(invader->y3);

    cJSON_AddItemToObject(invaderJSON,"tipo",tipo);
    cJSON_AddItemToObject(invaderJSON,"vida",vida);
    cJSON_AddItemToObject(invaderJSON,"puntos",puntos);
    cJSON_AddItemToObject(invaderJSON,"ID",ID);
    cJSON_AddItemToObject(invaderJSON,"x1",x1);
    cJSON_AddItemToObject(invaderJSON,"y1",y1);
    cJSON_AddItemToObject(invaderJSON,"x2",x2);
    cJSON_AddItemToObject(invaderJSON,"y2",y2);
    cJSON_AddItemToObject(invaderJSON,"x3",x3);
    cJSON_AddItemToObject(invaderJSON,"y3",y3);

    cJSON_AddItemToObject(invaderJSON,"misiles",MLtoJ(invader->misiles));

    return invaderJSON;
}

Invader* JtoIL(cJSON* json){
    Invader* invader = malloc(sizeof(Invader));

    invader->tipo = cJSON_GetObjectItem(json,"tipo");
    invader->ID = cJSON_GetObjectItem(json,"ID");
    invader->x1 = cJSON_GetObjectItem(json,"x1");
    invader->x2 = cJSON_GetObjectItem(json,"x2");
    invader->x3 = cJSON_GetObjectItem(json,"x3");
    invader->y1 = cJSON_GetObjectItem(json,"y1");
    invader->y2 = cJSON_GetObjectItem(json,"y2");
    invader->y3 = cJSON_GetObjectItem(json,"y3");
    invader->misiles = JtoML(cJSON_GetObjectItem(json,"tipo"));




}