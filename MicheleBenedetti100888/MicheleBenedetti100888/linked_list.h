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

/*
 Struttura dati dinamica per la memorizzazione
delle istruzioni da applicare ad un file.
 */
typedef struct list{
    edit_type type;
    unsigned int pos;
    char character;
    struct list *next;
}Lista;

/*
 Funzione per aggiungere un nodo in testa alla lista.
 */
void push(Lista** head_ref, edit_type type, unsigned int pos, char character);

/*
 Funzione per effettuare il reverse della lista.
 */
void reverse(Lista** head_ref);

/*
 Funzione per ottenere la stringa associata
 all'edit_type presente nella lista.
 */
char *getType(Lista *list);

/*
 Funzione per inserire il contenuto di un file
 in un buffer.
 */
char *createString(char *file);

#endif /* linked_list_h */
