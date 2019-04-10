//
// Created by jose on 08/04/19.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"

Node* createList(){
    Node* head = NULL;
    return head;
}

void add(Node** head, int data){
    Node* actual = *head;
    Node* newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    if(!*head){
        *head = newNode;
    } else{
        while (actual->next != NULL){
            actual = actual->next;
        }
        actual->next = newNode;
    }

}

void printList(Node *head){
    Node* actual = head;
    while(actual!=NULL){
        printf("[%d\t|\t%p]->\n", actual->data, actual->next);
        actual = actual->next;
    }
    printf("NULL \n");
}

void delete(Node** head, Node* target){
    Node* actual = *head;
    Node* previous = NULL;

    while(actual != NULL){
        if(actual->data = target->data){
            if(previous == NULL){
                *head = actual->next;
            }else{
                previous->next = actual->next;
            }
            free(actual);
            actual = actual->next;
        }
        previous = actual;
        actual = actual->next;
    }
}

void deleteList(Node** head){
    Node* actual = *head;
    Node* previous = *head;

    while(previous != NULL){
        actual = previous;
        previous = actual->next;
        if (previous != NULL){
            free(actual);
        }
    }
}