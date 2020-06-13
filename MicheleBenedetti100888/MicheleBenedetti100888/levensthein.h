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

char *saveOnFile(char *outputfile);

void readFromFile(char *filem);

int minimum(int a, int b, int c);

void deallocateMat(int size, int** mat);

void matCalculate(int **mat, char *str1, int x, char *str2, int y);

int levensthein_distance(char *file1, char *file2, int flag);

#endif /* levensthein_h */
