//
//  recursive.h
//  MicheleBenedetti100888
//
//  Created by Michele on 20/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#ifndef recursive_h
#define recursive_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "levensthein.h"

/*
 Struttura dati dinamica per la memorizzazione
 dei path e delle relative distance da inputfile.
 */
typedef struct pathFile
{
    char *path;
    int distance;
    struct pathFile *next;
} RecursiveList;

/*
Scan ricorsivo della directory per popolare la lista.
Richiamo delle relarive funzioni per search || searchall
*/

void getRecursive(char *inputfile, char *basepath, int limit);

#endif /* recursive_h */
