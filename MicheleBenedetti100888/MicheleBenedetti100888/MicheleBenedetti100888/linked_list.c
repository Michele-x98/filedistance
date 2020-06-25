//
//  linked_list.c
//  MicheleBenedetti100888
//
//  Created by Michele on 11/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "linked_list.h"

void push(Lista** head_ref, edit_type type, unsigned int pos, char character)
{
    Lista* new_node = (Lista*)malloc(sizeof(Lista));
  
    new_node->type = (edit_type)malloc(sizeof(edit_type));
    new_node->character = (char)malloc(sizeof(char));
    new_node->pos  = (unsigned int)malloc(sizeof(unsigned int));
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

char *getType(Lista *list){
    switch (list->type) {
        case SET:
            return "SET";
            break;
        case ADD:
            return "ADD";
            break;
        case DEL:
            return "DEL";
            break;
    }
}

char *createString(char *file){
    FILE *fin = fopen(file , "r" );
    if(fin == NULL){
        perror("Could not open file");
        exit(1);
    }
    //apro il file e mi posiziono alla fine del file
    fseek(fin, 0L, SEEK_END);
    //salvo la lunghezza del file su sizeFin
    long sizeFin = ftell(fin);
    //mi riposiziono all'inizio del file
    rewind(fin);
    //creo un buffer grande sizefin
    char *str = calloc(1, sizeFin);
    //inserisco il contenuto del file in str
    if(str != NULL){
        fread(str , sizeFin, 1 , fin);
    }
    fclose(fin);
    return str;
}
