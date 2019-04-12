//
// Created by jose on 11/04/19.
//

#include <stdio.h>
#include <stdlib.h>
#include "InvaderHandler.h"
InvaderHandler* createHandler(){
    InvaderHandler* handler = malloc(sizeof(InvaderHandler));
    handler->invaderList=createList();
    return handler;
}

void newEnemies(InvaderHandler* handler){
    char tipo;
    for(int i = 0; i < 7; i++){
        if(handler->IDcounter % 3 == 0){
            tipo = 'a';
        }else if(handler->IDcounter % 3 == 1){
            tipo = 'b';
        }else{
            tipo = 'c';
        }

        Invader* invader = createInvader(tipo,i*100+150,100,handler->IDcounter);
        add(&handler->invaderList, invader);

        handler->IDcounter++;
    }
}