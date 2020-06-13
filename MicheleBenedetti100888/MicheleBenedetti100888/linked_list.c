//
//  linked_list.c
//  MicheleBenedetti100888
//
//  Created by Michele on 11/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "linked_list.h"

void push(Lista** head_ref, edit_type type, int pos, char character)
{
    Lista* new_node = (Lista*)malloc(sizeof(Lista));
  
    new_node->type = (edit_type)malloc(sizeof(edit_type));
    new_node->character = (char)malloc(sizeof(char));
    new_node->pos  = (int)malloc(sizeof(int));
    new_node->next = (*head_ref);
    new_node->type = type;
    new_node->character = character;
    new_node->pos = pos;
    (*head_ref) = new_node;
}

void reverse(Lista** head_ref){
    Lista *prev = NULL;
    Lista *current = *head_ref;
    Lista *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void printList(Lista *node)
{
    while (node != NULL)
    {
        printf("Type: %u \n", node->type);
        printf("Pos: %i \n", node->pos);
        printf("Char: %c \n", node->character);
        node = node->next;
    }
}
