#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "functions.h"

FILE *openArchive(char *fileName){
    FILE *archive;

    archive = fopen(fileName, "r");

    return archive;
}

void readNumbers(FILE *archive, int *fileNumbers){
    rewind(archive);

    for(int i = 0; i < 10; i++)
        fscanf(archive, "%d ", &fileNumbers[i]);
}

tree *createsNew(int fileNumber){
    tree *new = (tree*) malloc(sizeof(tree));
    new->value = fileNumber;
    new->left = NULL;
    new->right = NULL;

    return new;
}

tree *insert(tree *root, tree *new){
    if(root == NULL)
        return new;
    if(root->value > new->value)
        root->left = insert(root->left, new);
    else
        root->right = insert(root->right, new);

    return root;
}

tree *loadTreeFromFile(char *fileName){
    FILE *archive;
    tree *root = NULL, *new = NULL;
    int totalOfNumbersInFile, *fileNumbers = NULL;

    archive = openArchive(fileName);

    if(archive == NULL){
        printf("Cannot open file!");
        getchar();
    }
    else{
        fileNumbers = calloc(totalOfNumbersInFile, sizeof(int));
        readNumbers(archive, fileNumbers);
        fclose(archive);
        for(int i = 0; i < 10; i++){
            new = createsNew(fileNumbers[i]);
            root = insert(root, new);
        }
    }

    return root;
}

void showTree(tree *root){
    if (root != NULL){
        printf("%d ", root->value);
        showTree(root->left);
        showTree(root->right);
    }
}

int isFull(tree *root){
    if(root == NULL)
        return 1;
    if(root->left == NULL && root->right == NULL)
        return 1;
    if((root->left) && (root->right))
        return (isFull(root->left) && isFull(root->right));

    return 0;
}

void searchValue(tree *root, int value){
    if (root != NULL){
        if(value == root->value){
            printf("Root Node\n");
            return;
        }
        else if((root->left != NULL) && value < root->value){
            if(root->left->value == value){
                printf("Dad: %d\n",root->value);
                if(root->right != NULL)
                    printf("Brother: %d\n", root->right->value);
                else
                    printf("This node doesn't have brother\n");
                return;
            }
            searchValue(root->left, value);
        }
        else if((root->right != NULL)){
            if(root->right->value == value){
                printf("Dad: %d\n",root->value);
                if(root->left != NULL)
                    printf("Brother: %d\n", root->left->value);
                else
                    printf("This node doesn't have brother\n");
                return;
            }
            searchValue(root->right, value);
        }
        else
            printf("Node not found in the tree\n");
    }
}

int getHeight(tree *root){
    int leftH, rightH, height;

    if (root == NULL){
        return 0;
    }

    leftH = getHeight(root->left);
    rightH = getHeight(root->right);
    height = leftH > rightH ? leftH + 1 : rightH + 1;

    return height;
}

void removeValue(tree *root, int valueDeleted){
}

void printInOrder(tree* root){
    if (root != NULL){
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

void printPreOrder(tree *root){
    if (root != NULL){
        printf("%d ", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPostOrder(tree *root){
    if (root != NULL){
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->value);
    }
}

void balanceTree(tree *root){
}

void menu(){
    printf("\n==================== MENU =========================\n");
    printf("Choose one of the options below: \n");
    printf("0 - EXIT\n");
    printf("1 - Load tree from file\n");
    printf("2 - Show tree\n");
    printf("3 - Is full\n");
    printf("4 - Search value\n");
    printf("5 - Get height\n");
    printf("6 - Remove value\n");
    printf("7 - Print in order\n");
    printf("8 - Print pre order\n");
    printf("9 - Print post order\n");
    printf("10 - Balance tree\n");
    printf("\t\tOption: ");
}
