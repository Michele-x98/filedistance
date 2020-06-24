//
//  levensthein.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "levensthein.h"

int minimum(int a, int b, int c);

/*
Funzione per riempire la matrice
Restiusco la matrice riempita.
*/
int **initMatrix(int **matrix, char *str1, int x, char *str2, int y);

int minimum(int a, int b, int c) {

    int min = a;

    if (b < min) min = b;
    if (c < min) min = c;

    return min;
}

void deallocateMat(int size, int** mat){
    for (int i = 0; i<size; i++) {
        free(mat[i]);
    }
    free(mat);
}

//TODO: CANCELLO PRIMA DELLA CONSEGNA
void PrintMatrix(int **matrix, int rows, int columns){
    
    printf("\n");
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

Lista *matCalculate(int **mat, char *str1, int x, char *str2, int y){
    
    Lista *list = NULL;
    //mi posiziono alla fine della matrice
    int curr = mat[x][y];
    
    int prev = 0, add = 0, del = 0, set = 0;
    
    while (curr !=0) {
        if (x == 0) {
            del = mat[x][y-1];
            prev = mat[x][y-1];
        }else if(y == 0){
            add = mat[x-1][y];
            prev = mat[x-1][y];
        }else if(x > 0 && y >0){
    add = mat[x-1][y];
    set = mat[x-1][y-1];
    del = mat[x][y-1];
    prev = minimum(del, set, add);
    }
    //SET
    if(prev == set){
        curr = prev;
        if(str1[x-1] != str2[y-1]){
            printf("REPLACE CHAR: %c at POS: %i \n", str1[x-1], y);
            push(&list,SET,y ,str1[x-1]);
        }
    x--;y--;
    }else if(prev == add){
        //ADD
        curr = prev;
        printf("ADD CHAR: %c AT POS: %i \n", str1[x-1], y);
        push(&list, ADD, y, str1[x-1]);
        x--;
        }
        else if(prev == del){
            curr = prev;
            //DEL
            printf("DELETE CHAR AT POS: %i \n", y);
            push(&list, DEL, y, ' ');
            y--;
        }
    }
    reverse(&list);
    return list;
}

int **initMatrix(int **matrix, char *str1, int x, char *str2, int y){
    int cost = 0;
    
    for(int i=1; i<x; i++){
        for(int j=1; j<y; j++){
            
            if (str1[i - 1] == str2[j - 1])
                cost = 0;
            else
                cost = 1;
            int del = matrix[i - 1][j] + 1;
            int add = matrix[i][j - 1] + 1;
            int set = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = minimum(del, add, set);
        }
    }
    return matrix;
}

int **matGenerate(char *str1, int x, char *str2, int y){
    
    int **mat = malloc(sizeof(int*) * x);
    if(mat != NULL)
    for (int i=0; i<x; i++){
        mat[i] = calloc(1, sizeof(int) * y);
    }
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            mat[i][0]=i;
            mat[0][j]=j;
        }
    }
    return initMatrix(mat, str1, x, str2, y);
}

int levensthein_distance(char *file1, char *file2){
    
    char *str1 = createString(file1); //creo prima stringa
    char *str2 = createString(file2); //creo secondo stringa
    
    int x = (int) strlen(str1)+1; //prendo lunghezza di str1
    int y = (int) strlen(str2)+1; //prendo lunghezza di str2
    
    //Base case
    if (x == 0)
        return y;
    if (y == 0)
        return x;

    int **matrix = matGenerate(str1, x, str2, y); //prendo matrice calcolata
    int distance = matrix[x-1][y-1]; //leggo distance di edit
    deallocateMat(x, matrix); //dealloco memoria della matrice
    free(str1); //dealloco memoria str1
    free(str2); //dealloco memoria str2
    return distance;
}

void generateBinaryFile(char *outputfile, Lista *list){
    FILE *filebin;
    if ((filebin = fopen(outputfile,"wb+")) == NULL){
        perror("Could not open file");
        exit(1);
    }
    
    char* command = NULL;
    unsigned int num = 0;
    
    while (list != NULL) {
        switch (list->type) {
            case DEL:
                command = getType(list); //prendo il comando
                for (int i = 0; i<3; i++) {
                    //scrio carattere per carattere nel file bin
                    fwrite(&command[i], sizeof(char), 1, filebin);
                }
                //scrivo posizione nel carattere successivo
                fwrite(&list->pos, sizeof(unsigned int), 1, filebin);
                break;
            case ADD:
                command = getType(list);
                for (int i = 0; i<3; i++) {
                    fwrite(&command[i], sizeof(char), 1, filebin);
                }
                num = list->pos;
                fwrite(&num, sizeof(unsigned int), 1, filebin);
                fwrite(&list->character, sizeof(char), 1, filebin);
                break;
            case SET:
                command = getType(list);
                for (int i = 0; i<3; i++) {
                    fwrite(&command[i], sizeof(char), 1, filebin);
                }
                num = list->pos;
                fwrite(&num, sizeof(unsigned int), 1, filebin);
                fwrite(&list->character, sizeof(char), 1, filebin);
                break;
        }
        list = list->next;
    }
    fclose(filebin);
}
