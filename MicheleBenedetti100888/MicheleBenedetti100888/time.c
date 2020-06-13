//
//  time.c
//  MicheleBenedetti100888
//
//  Created by Michele on 09/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "time.h"

time_t start, end;

void start_timer(){
    start = clock();
};

double stop_timer(){
        end = clock();
        double execution_time = (double)(end - start) / CLOCKS_PER_SEC;
        return execution_time;
};
