//
// Created by jose on 08/04/19.
//

#ifndef SPACEINVADERS_LINKEDLIST_H
#define SPACEINVADERS_LINKEDLIST_H

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* createList();

void add(Node** head, int data);

void printList(Node* head);

void delete(Node** head, Node* target);

void  deleteList(Node** head);
#endif //SPACEINVADERS_LINKEDLIST_H
