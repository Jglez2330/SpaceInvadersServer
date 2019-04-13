//
// Created by Fabricio on 9/4/2019.
//

#include "misil.h"

//Función que va cambiando las posiciones de los misiles disparados por el usuario
void MisilAvanza(Misil *misil)
{
    misil->y1 += misil->vy;
    misil->y2 += misil->vy;
}

//Función que libera la memoria de los misiles que salen del rango de la pantalla


int colisiones(SDL_Rect *rect1, SDL_Rect *rect2)
{
    if(rect1->y >= rect2->y + rect2->h){
        return 0;
    }
    else if(rect1->x >= rect2->x + rect2->w){
        return 0;
    }
    else if(rect1->y + rect1->h <= rect2->y){
        return 0;
    }
    else if(rect1->x + rect1->w <= rect2->x){
        return 0;
    }
    else{
        return 1;
    }

}

SDL_Rect crearRectanguloMisil(Misil *misil)
{
    SDL_Rect retorno;
    retorno.x = misil->x1;
    retorno.y = misil->y1;
    retorno.w = 3;
    retorno.h = 3;
    return retorno;

}

cJSON* MLtoJ(Misil* misil){
    cJSON* misilJSON = cJSON_CreateArray();

    Misil* actual = misil;
    while (actual != NULL) {

        cJSON *x1 = cJSON_CreateNumber(misil->x1);
        cJSON *y1 = cJSON_CreateNumber(misil->y1);
        cJSON *x2 = cJSON_CreateNumber(misil->x2);
        cJSON *y2 = cJSON_CreateNumber(misil->y2);
        cJSON *vy = cJSON_CreateNumber(misil->vy);

        cJSON* temp = cJSON_CreateObject();

        cJSON_AddItemToObject(temp,"x1",x1);
        cJSON_AddItemToObject(temp,"y1",y1);
        cJSON_AddItemToObject(temp,"x2",x2);
        cJSON_AddItemToObject(temp,"y2",y2);
        cJSON_AddItemToObject(temp,"vy",vy);

        cJSON_AddItemToArray(misilJSON,temp);

        actual = actual->siguiente;
    }

    return misilJSON;
}

Misil* JtoML(cJSON* json){

    //Todo:Hacer la funcion

}