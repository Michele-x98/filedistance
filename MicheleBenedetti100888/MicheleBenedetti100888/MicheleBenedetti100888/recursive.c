//
//  recursive.c
//  MicheleBenedetti100888
//
//  Created by Michele on 20/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "recursive.h"

RecursiveList *dirList = NULL;

/*
Aggiunta di un nodo alla lista
*/
void add(RecursiveList **head, char *path, int distance);

/*
Scan ricorsivo della directory basePath.
Aggiunta della distanza e del path relativo alla lista.
*/
void listFilesRecursively(char *inputfile, char *basePath);

/*
 Funzione per l'Algoritmo del MergeSort
 */
void MergeSort(RecursiveList **headRef);

RecursiveList *SortedMerge(RecursiveList *a, RecursiveList *b);

void FrontBackSplit(RecursiveList *source, RecursiveList **frontRef, RecursiveList **backRef);

/*
Ordino la lista in modo crescente e stampo i pathAssoluti
dei file con distanza minore o uguale a limit.
*/
void printLimitDistance(int limit);

/*
Ordino la lista in modo crescente e stampo i pathAssoluti
con minor distanza da inputfile.
*/
void printMinDistance(void);

void add(RecursiveList **head, char *path, int distance)
{
    RecursiveList *new_node = (RecursiveList *)malloc(sizeof(RecursiveList));

    new_node->path = malloc((strlen(path) + 1) * sizeof(char));
    new_node->distance = (int)malloc(sizeof(int));
    new_node->next = (*head);
    strcpy(new_node->path, path);
    new_node->distance = distance;
    (*head) = new_node;
}

void listFilesRecursively(char *inputfile, char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".DS_Store"))
        {
            strcpy(path, basePath);
            //concateno "/" e creo il path relativo successivo
            strcat(path, "/");
            strcat(path, dp->d_name);
            /*Se non è una directory, eseguo levensthein,
             aggiungo il pathrelativo e distance alla lista*/
            if (dp->d_type != DT_DIR)
            {
                int distance = levensthein_distance(inputfile, path);
                add(&dirList, path, distance);
            }
            listFilesRecursively(inputfile, path);
        }
    }
    closedir(dir);
}

void printLimitDistance(int limit)
{
    MergeSort(&dirList);
    while (dirList != NULL)
    {
        char *real_path = realpath(dirList->path, NULL); //sizeof NULL permette di andare oltre il limite PATH_MAX
        if (dirList->distance <= limit)
        {
            printf("%i \t %s \n", dirList->distance, real_path);
        }
        free(real_path);
        free(dirList->path);
        dirList = dirList->next;
    }
    free(dirList);
}

void printMinDistance(void)
{
    MergeSort(&dirList);
    printLimitDistance(dirList->distance);
}

void getRecursive(char *inputfile, char *basepath, int limit)
{
    listFilesRecursively(inputfile, basepath);
    if (limit != -1)
    {
        printLimitDistance(limit);
    }
    else
    {
        printMinDistance();
    }
}

RecursiveList *SortedMerge(RecursiveList *a, RecursiveList *b)
{
    RecursiveList *result = NULL;
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    /* Pick either a or b, and recur */
    if (a->distance <= b->distance)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(RecursiveList *source, RecursiveList **frontRef, RecursiveList **backRef)
{
    RecursiveList *fast;
    RecursiveList *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void MergeSort(RecursiveList **headRef)
{
    RecursiveList *head = *headRef;
    RecursiveList *a;
    RecursiveList *b;
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = SortedMerge(a, b);
}
