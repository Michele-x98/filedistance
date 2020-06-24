//
//  modfile.h
//  MicheleBenedetti100888
//
//  Created by Michele on 24/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#ifndef modfile_h
#define modfile_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/*
Legge le modifiche presenti in "filem.bin" da applicare a "inputfile".
Genera il file "outputfile" con le modifiche applicate.
*/
void modifyFile(char *inputfile, char *filem, char *outputfile);

/*
Funzione per leggre le istruzioni da un file .bin e inserirle
all'interno di una lista. Restituisce la lista di istruzioni.
*/
Lista *readFromBinFile(char *filem);

/*
Genero (se non esiste) e scrivo la stringa "string"
nel file "outputfile"
*/
void generateOutputFile(char *outputfile, char *string);

/*
Funzione per aggiungere un carattere "character" in una
determinata posizione "pos" in una stringa "string"
*/
char *addChar(char *string, unsigned int pos, char character);

/*
Funzione per cancellare un carattere dalla
stringa "string" alla posizione "pos"
*/
char *delChar(char *string, unsigned int pos);

/*
Funzione per cambiare un carattere "character"
alla posizione "pos" della stringa "string"
*/
char *setChar(char *string, unsigned int pos, char character);

#endif /* modfile_h */
