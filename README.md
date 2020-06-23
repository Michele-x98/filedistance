# filedistance
Progetto in C per corso di Sistemi Operativi Laboratorio.

## Progetto Laboratorio di Sistemi Operativi Giugno/Luglio 2020
La *distanza di edit* è una funzione che consente di verificare quanto due stringhe (o sequenze di byte) siano *lontane* una dall’altra. Questa distanza viene calcolata sulla base del numero di operazioni necessarie a trasformare una stringa nell’altra. Le operazioni sono:
* Aggiungere un carattere/byte;
* Eliminare un carattere/byte;
* Modificare un carattere/byte.

Per calcolare la distanza di edit è possibile utilizzare l’algoritmo di ​Wagner–Fischer.

## Il programma *filedistance*
Occorre realizzare il programma ​filedistance​ che implementa le seguenti funzionalità:
1. **Calcolo della distanza tra due file**: ​dati due file ​f1 e ​f2,​ il programma produce in output la distanza tra *f1* ed *f2*. Opzionalmente, il programma potrà anche generare la minima sequenza di operazioni necessarie per trasformare *f1* in *f2*. Tale sequenza
viene rappresentata attraverso una sequenza di istruzioni:

  * ADD*nb*: n è un intero senza segno (unsigned int) rappresentato con 4 byte
(byte più significativo all’inizio) mentre ​b è un singolo byte. Tale operazione
indica che viene aggiunto il byte ​b n​ ella posizione ​n​.
  * DEL*n*: n è un intero senza segno (unsigned int). Tale operazione indica che
viene eliminato il byte​ n​ ella posizione ​n.​
  * SET*nb*: n è un intero senza segno (unsigned int) rappresentato con 4 byte
mentre ​b è un singolo byte. Tale operazione indica che valore del byte in
posizione ​n ​viene impostato a ​b.

Queste istruzioni potranno essere salvate in un file per successive elaborazioni. I valori ADD, DEL e SET vengono salvati in binario con i byte corrispondenti alle lettere. Inoltre le istruzioni devono apparire in ordine.

2. **Applicazione delle modifiche ad un file**: ​dato un file ​f1 contenente ed un file da elaborare ed un file ​m contenente la lista di ​modifiche da apportare ​(secondo il formato descritto sopra) p​ roduce in output un file ​f2 ​ottenuto da ​f1 ​applicando le modifiche indicate in ​m.

3. **Ricerca di file**: ​dato un file *f* ed una directory ​d viene restituito l’insieme dei file a distanza *minima* d a *f*.
## Opzioni del programma
Per poter eseguire le funzionalità descritte sopra il programma potrà essere eseguito con le seguenti opzioni:
### Calcolo distanza tra file:


>- *filedistance distance file1 file2*
>- *filedistance distance file1 file2 output*

Nel primo caso, dove vengono passati come argomenti i due file da confrontare, viene calcolata la distanza dal file e generato un output della seguente forma:

>- EDIT DISTANCE: *distanza*
>- TIME: *tempo di calcolo*

Nel secondo caso, invece, verranno salvate nel file *output* la sequenza delle istruzioni necessarie per trasformare il primo file nel secondo.

### Applicazione delle modifiche:

>- *filedistance apply inputfile filem outputfile*

Applica a *inputfile* le modifiche contenute nel file *filem* e salva il risultato nel file *outputfile•.

### Ricerca di file:

>- *filedistance search inputfile dir*

Restituisce in output i file contenuti in *dir* (e nelle sue sottodirectory) che hanno minima distanza da •inputfile*. Il path assoluto di ogni file viene presentato in una riga dello *standard output*.

>- *filedistance searchall inputfile dir limit*

Vengono restituiti in output tutti i file contenuti in dir (e nelle sue sottodirectory) che hanno una distanza da *inputfile* minore o uguale di *limit* (che è un intero). I file vengono presentati nello standard output in ordine crescente secondo il seguente formato:

> *distanza pathassolutofile*
