//
//  modfile.c
//  MicheleBenedetti100888
//
//  Created by Michele on 24/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "modfile.h"

Lista *readFromBinFile(char *filem){
    FILE *binfile = fopen(filem, "rb+");
    if(binfile == NULL){
        perror("Could not open file");
        exit(1);
    }
    
    Lista *list = NULL;
    char command;
    unsigned int pos = 0;
    char c;
    /*
     Scorro il file binario, prendo il primo byte e salvo il valore in command.
     Mi sposto di 2 con fseek per prendere il valore intero e
     se command = S o A, mi sposto alla posizione successiva per
     per prendere il char corrispondente, altrimenti command = D, quindi mi fermo.
     */
    while (!feof(binfile)) {
        fread(&command, sizeof(char), 1, binfile);
        switch (command) {
            case 'S':
                fseek(binfile, 2, SEEK_CUR);
                fread(&pos, (sizeof(unsigned int)), 1, binfile);
                fread(&c, (sizeof(char)), 1, binfile);
                push(&list, SET, pos, c); //Aggiungo il comando, la posizione e il carattere nella lista
                command = '\0';
                break;
            case 'A':
                fseek(binfile, 2, SEEK_CUR);
                fread(&pos, (sizeof(unsigned int)), 1, binfile);
                fread(&c, (sizeof(char)), 1, binfile);
                push(&list, ADD, pos, c); //Aggiungo il comando, la posizione e il carattere nella lista
                command = '\0';
                break;
            case 'D':
                fseek(binfile, 2, SEEK_CUR);
                fread(&pos, (sizeof(unsigned int)), 1, binfile);
                push(&list, DEL, pos, ' '); //Aggiungo il comando e la posizione nella lista
                command = '\0';
                break;
        }
    }
    reverse(&list); //reverse della lista
    fclose(binfile);
    return list;
}

void generateOutputFile(char *outputfile, char *string){
    FILE *fout = fopen(outputfile, "w");
    if (fout == NULL) {
        perror("Could not open file");
        exit(1);
    }
    fputs(string, fout);
}

char *addChar(char *string, unsigned int pos, char character){
        int i, len;
        char *temp = NULL;
        len = string ? (unsigned int)strlen(string) : 0;
        temp = (char *)calloc(1, len + 2);
        if (temp != NULL) {
            /* controllo posizione */
            if (pos > len)
                pos = len;
            /* copio prima parte */
            for (i = 0; i <pos; i++) {
                temp[i] = string[i];
            }
            /* inserisco il carattere */
            temp[i] = character;
            /* copio il restante della stringa se presente */
            for (; i < len; i++) {
                temp[i + 1] = string[i];
            }
            /* aggiungo il terminatore di stringa */
            temp[i + 1] = '\0';
            free(string);
        }
        return temp;
}

char *delChar(char *string, unsigned int pos){
    char *temp = NULL;
    temp = memmove(&string[pos], &string[pos + 1], strlen(string) - pos);
    return string;
}

char *setChar(char *string, unsigned int pos, char character){
    string[pos] = character;
    return string;
}

void modifyFile(char *inputfile, char *filem, char *outputfile){
    
    //prendo lista di istruzioni ordinata
    Lista *list = readFromBinFile(filem);
    //prendo stringa
    char *string = createString(inputfile);
    
    //scorro la lista e applico le modifiche
    while (list != NULL) {
        switch (list->type) {
            case SET:
                string = setChar(string, list->pos-1, list->character);
                break;
            case DEL:
                string = delChar(string, list->pos-1);
                break;
            case ADD:
                string = addChar(string, list->pos, list->character);
                break;
        }
        list = list->next;
    }
    generateOutputFile(outputfile, string); //scrivo nel file la stringa
}

