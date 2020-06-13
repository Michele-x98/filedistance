//
//  linked_list.h
//  MicheleBenedetti100888
//
//  Created by Michele on 11/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#ifndef linked_list_h
#define linked_list_h

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SET,
    ADD,
    DEL,
} edit_type;

typedef struct list{
    edit_type type;
    int pos;
    char character;
    struct list *next;
}Lista;

void push(Lista** head_ref, edit_type type, int pos, char character);

void reverse(Lista** head_ref);

void printList(Lista *node);

#endif /* linked_list_h */
