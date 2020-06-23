//
//  levensthein.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "levensthein.h"

int minimum(int a, int b, int c);

void generateBinaryFile(char *outputfile, Lista *list);

void deallocateMat(int size, int** mat);

Lista *matCalculate(int **mat, char *str1, int x, char *str2, int y);

char *createString(char *file);

int **matGenerate(char *str1, int x, char *str2, int y);

int **initMatrix(int **matrix, char *str1, int x, char *str2, int y);

Lista *readFromBinFile(char *filem);

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

//TODO: Cancello
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
    printList(list);
    return list;
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
    if(str != NULL){
        fread(str , sizeFin, 1 , fin);
    }
    fclose(fin);
    return str;
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
    int **matApp = initMatrix(mat, str1, x, str2, y);
    //PrintMatrix(matApp, x, y);
    return matApp;
}

int levensthein_distance(char *file1, char *file2){
    
    char *str1 = createString(file1); //da modificare
    char *str2 = createString(file2); //target

    int x = (int) strlen(str1)+1;
    int y = (int) strlen(str2)+1;
    
    //Base case
    if (x == 0)
        return y;
    if (y == 0)
        return x;
    
    int **matrix = matGenerate(str1, x, str2, y);
    int distance = matrix[x-1][y-1];
    deallocateMat(x, matrix);
    free(str1);
    free(str2);
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
                command = getType(list);
                for (int i = 0; i<3; i++) {
                    fwrite(&command[i], sizeof(char), 1, filebin);
                }
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

void instructionGenerate(char *file1, char *file2, char *output){
    char *str1 = createString(file1);
    char *str2 = createString(file2);

    int x = (int) strlen(str1)+1;
    int y = (int) strlen(str2)+1;
    
    int **matrix = matGenerate(str1, x, str2, y);
    PrintMatrix(matrix, x, y);
    generateBinaryFile(output, matCalculate(matrix, str1, (x-1), str2, (y-1)));
    deallocateMat(x, matrix);
    free(str1);
    free(str2);
}

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
    
    while (!feof(binfile)) {
        fread(&command, sizeof(char), 1, binfile);
        switch (command) {
            case 'S':
                fseek(binfile, 2, SEEK_CUR);
                fread(&pos, (sizeof(unsigned int)), 1, binfile);
                fread(&c, (sizeof(char)), 1, binfile);
                push(&list, SET, pos, c);
                command = '\0';
                break;
            case 'A':
                fseek(binfile, 2, SEEK_CUR);
                fread(&pos, (sizeof(unsigned int)), 1, binfile);
                fread(&c, (sizeof(char)), 1, binfile);
                push(&list, ADD, pos, c);
                command = '\0';
                break;
            case 'D':
                fseek(binfile, 2, SEEK_CUR);
                fread(&pos, (sizeof(unsigned int)), 1, binfile);
                push(&list, DEL, pos, ' ');
                command = '\0';
                break;
        }
    }
    reverse(&list);
    printList(list);
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
        len = string ? (unsigned int) strlen(string) : 0;
        temp = (char *)calloc(1, len + 2);
        if (temp != NULL) {
            /* sanitize position */
            if (pos > len)
                pos = len;
            /* copy initial portion */
            for (i = 0; i <pos; i++) {
                temp[i] = string[i];
            }
            /* insert new character */
            temp[i] = character;
            /* copy remainder of the source string if any */
            for (; i < len; i++) {
                temp[i + 1] = string[i];
            }
            /* set the null terminator */
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
    
    Lista *list = readFromBinFile(filem);
    char *string = createString(inputfile);
    
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
    generateOutputFile(outputfile, string);
}

