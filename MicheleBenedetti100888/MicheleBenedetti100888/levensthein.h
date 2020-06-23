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
#include <dirent.h>
#include "linked_list.h"

void instructionGenerate(char *file1, char *file2, char *output);

Lista *readFromBinFile(char *filem);

int levensthein_distance(char *file1, char *file2);

void modifyFile(char *inputfile, char *filem, char *outputfile);

#endif /* levensthein_h */
