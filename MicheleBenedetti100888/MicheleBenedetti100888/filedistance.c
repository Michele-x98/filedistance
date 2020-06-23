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
    int distance = levensthein_distance(file2, file1);
    printf("\nEDIT DISTANCE: %i \n", distance);
    printf("TIME: %lf \n\n", stop_timer());
}

void distanceOutput(char *file1, char *file2, char *outputfile){
    start_timer();
    instructionGenerate(file2, file1, outputfile);
    printf("TIME: %lf\n", stop_timer());
}

void apply(char *inputfile, char *filem, char *outputfile){
    start_timer();
    modifyFile(inputfile, filem, outputfile);
    printf("TIME: %lf\n", stop_timer());
}

void search(char *inputfile, char *dir){
    start_timer();
    getRecursive(inputfile, dir, -1);
    printf("TIME: %lf\n", stop_timer());
}

void searchAll(char *inputfile, char *dir, int limit){
    start_timer();
    getRecursive(inputfile, dir, limit);
    printf("TIME: %lf\n", stop_timer());
}
