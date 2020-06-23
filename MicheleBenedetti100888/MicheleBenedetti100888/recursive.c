//
//  recursive.c
//  MicheleBenedetti100888
//
//  Created by Michele on 20/06/2020.
//  Copyright © 2020 Michele. All rights reserved.
//

#include "recursive.h"

RecursiveList *list = NULL;

void add(RecursiveList** head, char *path, int distance);

void listFilesRecursively(char *inputfile, char *basePath);

void MergeSort(RecursiveList** headRef);

void printLimitDistance(RecursiveList *list, int limit);

void printMinDistance(RecursiveList *list);

void add(RecursiveList** head, char *path, int distance)
{
    RecursiveList* new_node = (RecursiveList*)malloc(sizeof(RecursiveList));

    new_node->path = (char*)malloc((strlen(path) + 1) * sizeof(char));
    new_node->distance  = (int)malloc(sizeof(int));
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
            strcat(path, "/");
            strcat(path, dp->d_name);
            int distance = levensthein_distance(inputfile, path);
            add(&list, path, distance);
            listFilesRecursively(inputfile ,path);
        }
    }
    closedir(dir);
}

void printAll(RecursiveList *list){
    MergeSort(&list);
    while (list!=NULL) {
        printf("Path: %s \n", list->path);
        list = list->next;
    }
}

void printLimitDistance(RecursiveList *list, int limit){
    MergeSort(&list);
    while (list != NULL) {
        char *real_path = realpath(list->path, NULL);
        if (list->distance <= limit){
            printf("D: %i \t P: %s \n",list->distance, real_path);
        }
        list = list->next;
    }
}

void printMinDistance(RecursiveList *list){
    MergeSort(&list);
    printLimitDistance(list, list->distance);
}

void getRecursive(char *inputfile, char *basepath, int limit){
    listFilesRecursively(inputfile, basepath);
    if(limit != -1){
        printLimitDistance(list, limit);
    }else{
        printMinDistance(list);
    }
}

RecursiveList* SortedMerge(RecursiveList* a, RecursiveList* b)
{
    RecursiveList* result = NULL;
  
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
  
    /* Pick either a or b, and recur */
    if (a->distance <= b->distance) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(RecursiveList* source, RecursiveList** frontRef, RecursiveList** backRef)
{
    RecursiveList* fast;
    RecursiveList* slow;
    slow = source;
    fast = source->next;
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void MergeSort(RecursiveList** headRef)
{
    RecursiveList* head = *headRef;
    RecursiveList* a;
    RecursiveList* b;
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
