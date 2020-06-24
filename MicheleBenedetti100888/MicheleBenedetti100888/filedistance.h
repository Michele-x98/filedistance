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
#include "recursive.h"
#include "modfile.h"

/*
 Calcolo della distanza di edit tra "file1" e "file2"
 */
void distance(char *file1, char *file2);

/*
Funzione per generare il file .bin con all'interno le istruzioni
per la modifica del "file1" affinchè abbia distanza 0 da "file2".
*/
void distanceOutput(char *file1, char *file2, char *outputfile);

/*
 Applica a ​inputfile l​ e modifiche contenute nel file ​filem
 e salva il risultato nel file ​outputfile​.
 */
void apply(char *inputfile, char *filem, char *outputfile);

/*
Restituisce in output i file contenuti in ​dir​ (e nelle sue sottodirectory) che hanno minima distanza da ​inputfile.​ Il path assoluto di ogni file viene presentato in una riga dello ​standard output.
 */
void search(char *inputfile, char *dir);

/*
 Vengono restituiti in output tutti i file contenuti in dir (e nelle sue sottodirectory) che hanno una distanza da ​inputfile ​minore o uguale di ​limit (​ che è un intero).
 */
void searchAll(char *inputfile, char *dir, int limit);

#endif /* filedistance_h */
