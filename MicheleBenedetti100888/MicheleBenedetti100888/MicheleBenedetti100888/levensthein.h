//
//  levensthein.h
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#ifndef levensthein_h
#define levensthein_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

/*
Funzione per deallocare la memoria della matrice
*/
void deallocateMat(int size, int** mat);

/*
Funzione per generare ed inizializzare la matrice
per l'algoritmo di Levensthein.
Restituisco la matrice calcolata.
*/
int **matGenerate(char *str1, int x, char *str2, int y);

/*
Funzione che prende in ingresso una matrice "mat", la stringa "str1" e la sua relativa lunghezza "x", la stringa "str2" e la sua relativa lunghezza "y", calcola le istruzioni da eseguire per modifichere la stringa1 nella stringa 2, le aggiunge ad una lista e la restituisce.
*/
Lista *matCalculate(int **mat, char *str1, int x, char *str2, int y);

/*
Funzione per generare il file .bin data una lista di istruzioni.
*/
void generateBinaryFile(char *outputfile, Lista *list);

/*
 Calcolo della distanza tra "file1" e "file2".
 Restituisce la distanza tra le 2 stringhe.
 */
int levensthein_distance(char *file1, char *file2);

#endif /* levensthein_h */
