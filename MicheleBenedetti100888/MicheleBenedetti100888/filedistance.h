//
//  filedistance.h
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#ifndef filedistance_h
#define filedistance_h

#include <stdio.h>
#include "time.h"
#include "levensthein.h"

void distance(char *file1, char *file2);

void distanceOutput(char *file1, char *file2, char *outputfile);

void apply(char *inputfile, char *filem, char *outputfile);

#endif /* filedistance_h */