//
//  filedistance.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "filedistance.h"

void distance(char *file1, char *file2){
    start_timer();
    int distance = levensthein_distance(file1, file2);
    printf("\nEDIT DISTANCE: %i \n", distance);
    printf("TIME: %lf \n\n", stop_timer());
}

void distanceOutput(char *file1, char *file2, char *outputfile){
    start_timer();
    instructionGenerate(file1, file2, outputfile);
    printf("TIME: %lf\n", stop_timer());
}

void apply(char *filem){
    readFromBinFile(filem);
}
