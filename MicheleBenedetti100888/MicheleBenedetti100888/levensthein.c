//
//  levensthein.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "levensthein.h"

Lista *list = NULL;

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

void matCalculate(int **mat, char *str1, int x, char *str2, int y){
    
    int curr = mat[x][y];

    while (curr !=0) {
    int del = mat[x-1][y];
    int set = mat[x-1][y-1];
    int add = mat[x][y-1];
    int prev = minimum(del, set, add);
        
    //SET
    if(prev == set){
        curr = prev;
        if(str1[x-1] != str2[y-1]){
            printf("REPLACE CHAR: %c at POS: %i \n", str2[y-1], x);
            push(&list,SET,x ,str2[y-1]);
        }
    x--;y--;
    }else if(prev == add){
        //ADD
        curr = prev;
        if (str1[x-1] != str2[y-1]) {
            printf("ADD CHAR: %c AT POS: %i \n", str2[y-1], x);
            push(&list, ADD, x, str2[y-1]);
            }
        y--;
        }
        else if(prev == del){
            curr = prev;
            //DEL
            if(str1[x-1] != str2[y-1]){
                printf("DELETE CHAR AT POS: %i \n", x);
                push(&list, DEL, x, ' ');
            }
            x--;
        }
    }
    reverse(&list);
    printList(list);
}

char *saveOnFile(char *outputfile){
    FILE *filebin;
    if ((filebin = fopen(outputfile,"wb+")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    
    while (list != NULL) {
        switch (list->type) {
            case DEL:
                fprintf(filebin, "DEL%i\n", list->pos);
                break;
            case ADD:
                fprintf(filebin, "ADD%i%s\n", list->pos, &list->character);
                break;
            case SET:
                fprintf(filebin, "SET%i%s\n", list->pos, &list->character);
                break;
        }
        list = list->next;
    }
    fclose(filebin);
    return outputfile;
}

void readFromFile(char *filem){
    
    Lista listApp;
    
    FILE *binfile;
    if((binfile = fopen(filem, "rb")) == NULL){
        perror("Can't open file");
        exit(1);
    }
    fseek(binfile, 0L, SEEK_END);
    long sizeBin = ftell(binfile);
    rewind(binfile);
    
    for (int i =0; i<sizeBin; i++) {
    
        fread(&listApp, sizeof(Lista), 1, binfile);
        printf("\nCHAR: %c \n", listApp.character);
        
    }
    fclose(binfile);
}

void PrintMatrix(int **matrix, int rows, int columns){
    
    printf("\n");
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

char *createString(char *file){
    FILE *fin = fopen(file , "r" );
    if(fin == NULL){
        perror("Could not open file");
        exit(1);
    }
    
    fseek(fin, 0L, SEEK_END);
    long sizeFin = ftell(fin);
    rewind(fin);
    
    char *str = calloc(1, sizeFin);
    fread(str , sizeFin, 1 , fin);
    fclose(fin);
    return str;
}

int **initMatrix(int **matrix, char *str1, int x, char *str2, int y){
    for(int i=1; i<x; i++){
        for(int j=1; j<y; j++){
            int min = minimum(matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1]);
                if( str1[i-1] == str2[j-1]){
                    matrix[i][j] = min;
                }else
                matrix[i][j] = min + 1;
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

int levensthein_distance(char *file1, char *file2, int flag){
    
    char *str1 = createString(file1);
    char *str2 = createString(file2);

    int x = (int) strlen(str1);
    int y = (int) strlen(str2);
    
    //Base case
    if (x == 0)
        return y;
    if (y == 0)
        return x;
    
    int **matrix = matGenerate(str1, x, str2, y);
    int distance = matrix[x-1][y-1];
    //PrintMatrix(matrix, x, y);
    if(flag == 0){
        matCalculate(matrix, str1, (x-1), str2, (y-1));
    }
    deallocateMat(x, matrix);
    free(str1);
    free(str2);
    return distance;
}
