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
#include "levensthein.h"

typedef struct directory{
    char *path;
    int distance;
    struct directory *next;
}RecursiveList;

void getRecursive(char *inputfile, char *basepath, int limit);

#endif /* recursive_h */
