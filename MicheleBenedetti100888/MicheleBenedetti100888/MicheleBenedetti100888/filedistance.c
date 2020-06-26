//
//  filedistance.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "filedistance.h"

void distance(char *file1, char *file2)
{
    start_timer();
    int distance = levensthein_distance(file2, file1);
    printf("\nEDIT DISTANCE: %i \n", distance);
    printf("TIME: %lf \n\n", stop_timer());
}

void distanceOutput(char *file1, char *file2, char *outputfile)
{
    start_timer();
    char *str1 = createString(file2); //creo str1 dal file2
    char *str2 = createString(file1); //creo str2 dal file1

    int x = (int)strlen(str1) + 1; //calcolo lunghezza di str1
    int y = (int)strlen(str2) + 1; //calcolo lunghezza di str2

    int **matrix = matGenerate(str1, x, str2, y); //prendo matrice calcolata
    //genero (se non esiste) il file .bin con le istruzioni
    generateBinaryFile(outputfile, matCalculate(matrix, str1, (x - 1), str2, (y - 1)));
    deallocateMat(x, matrix); //dealloco la memoria della matrice
    free(str1);               //dealloco la memoria di str1
    free(str2);               //dealloco la memoria di str2
    printf("TIME: %lf\n", stop_timer());
}

void apply(char *inputfile, char *filem, char *outputfile)
{
    start_timer();
    modifyFile(inputfile, filem, outputfile);
    printf("TIME: %lf\n", stop_timer());
}

void search(char *inputfile, char *dir)
{
    start_timer();
    getRecursive(inputfile, dir, -1);
    printf("TIME: %lf\n", stop_timer());
}

void searchAll(char *inputfile, char *dir, int limit)
{
    start_timer();
    getRecursive(inputfile, dir, limit);
    printf("TIME: %lf\n", stop_timer());
}
