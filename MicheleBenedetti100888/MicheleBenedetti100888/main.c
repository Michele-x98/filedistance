//
//  main.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filedistance.h"

void help(){
    printf("\n\t\t +++++++++ How to use +++++++++\n\n");
    printf("Edit distance from two file: ./filedistance distance <file1> <file2> \n");
    printf("Generete output instraction: ./filedistance distance <file1> <file2> <output> \n");
    printf("Apply instraction: ./filedistance apply <inputfile> <filem> <outputfile> \n");
    printf("Search file: ./filedistance search <inputfile> <dir> \n");
    printf("Search file with limit: ./filedistance searchall <inputfile> <dir> <limit> \n\n");
}

int main(int argc, char *argv[]) {
    
    if(argc == 1){
        help();
        exit(1);
    }else if (strcmp(argv[1], "distance") == 0){
        if (argc == 4) {
            distance(argv[2], argv[3]);
        }else if (argc == 5){
            distanceOutput(argv[2], argv[3], argv[4]);
        }else perror("Wrong number of arguments \n");
    }else if ((strcmp(argv[1], "apply") == 0) && (argc == 5)){
        apply(argv[2], argv[3], argv[4]);
    }else if ((strcmp(argv[1], "search") == 0) && (argc == 4)){
        search(argv[2], argv[3]);
    }else if ((strcmp(argv[1], "searchall") == 0) && (argc == 5)){
        int limit = atoi(argv[4]);
        searchAll(argv[2], argv[3], limit);
    }else perror("Wrong numeber of arguments \n");
    return 0;
}
