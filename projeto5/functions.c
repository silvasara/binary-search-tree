#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void insertNew(tree *t, int value){
    if(t==NULL){
        t=(tree *)malloc(sizeof (tree));
        t->left=NULL;
        t->right=NULL;
        t->value=value;
    }
    else{
        if(value < t->value){
            insertNew(t->left, value);
        }
        else{
            insertNew(t->right, value);
        }
    }
}

tree *loadTreeFromFile(char *archive_name){
    FILE *archive = fopen(archive_name, "r");
    if(archive == NULL){
        printf("oi\n");
    }   

    int numbers[10], i = 0;

    tree *t = NULL;

    for(int j = 0; j < 10; j++){
        fscanf(archive, "%d ", &numbers[i]);
        printf("%d ", numbers[i]);
    }

    for(int j = 0; j < 10; j++){
        insertNew(t, numbers[i]);
    }

    return t;
}

void printInOrder(tree *t){
    if(t != NULL){
        printInOrder(t->left);
        printf("%d ", t->value);
        printInOrder(t->right);
    }
}
