//
// Created by jose on 08/04/19.
//

#ifndef SPACEINVADERS_LINKEDLIST_H
#define SPACEINVADERS_LINKEDLIST_H

#include "invader.h"

typedef struct Node{
    struct Invader* data;
    struct Node* next;
}Node;

Node* createList();

void add(Node** head, Invader* data);

void printList(Node* head);

void delete(Node** head, int target);

void  deleteList(Node** head);
#endif //SPACEINVADERS_LINKEDLIST_H
