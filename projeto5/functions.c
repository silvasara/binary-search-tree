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

int readNumbers(FILE *archive){
    rewind(archive);
    int number,count=0;

    while(!feof(archive)){
      fscanf(archive, "%d ", &number);
      count++;
    }
    return count;
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
    totalOfNumbersInFile = readNumbers(archive);
    fileNumbers = calloc(totalOfNumbersInFile, sizeof(int));
    for(int i = 0 ; i<totalOfNumbersInFile;i++){
      fscanf(archive, "%d ", &fileNumbers[i]);
      printf("%d\n", fileNumbers[i] );
    }
    fclose(archive);
    for(int i = 0; i < totalOfNumbersInFile; i++){
      new = createsNew(fileNumbers[i]);
      root = insert(root, new);
    }
  }

  return root;
}

void print(tree *root, int level){
     int i;
     if(root == NULL)
        return;
     print(root->right, level+1);
     for(i=0;i<level;i++)
        printf("      ");
     printf("%6d\n\n",root->value);
     print(root->left,level+1);
}

void showTree(tree *root){
    print(root, 0);
}

int checksIsFull(tree *root){
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return 1;
    if((root->left) && (root->right))
        return (checksIsFull(root->left) && checksIsFull(root->right));
    return 2;
}

void isFull(tree *root){
    if(checksIsFull(root) == 1)
        printf("Tree is full!\n");
    else if(checksIsFull == 0)
        printf("Tree is empty!\n");
    else
        printf("Tree is not full\n");
}

void searchValue(tree *root, int value){
    int level;
    if (root != NULL){
        if(value == root->value){
            printf("Root Node\n");
            return;
        }
        else if((root->left != NULL) && value < root->value){
            if(root->left->value == value){
                level++;
                printf("Dad: %d\n",root->value);
                if(root->right != NULL)
                    printf("Brother: %d\n", root->right->value);
                else
                    printf("This value doesn't have brother\n");
                return;
            }
            searchValue(root->left, value);
        }
        else if((root->right != NULL)){
            if(root->right->value == value){
                level++;
                printf("Dad: %d\n",root->value);
                if(root->left != NULL)
                    printf("Brother: %d\n", root->left->value);
                else
                    printf("This value doesn't have brother\n");
                return;
            }
            searchValue(root->right, value);
        }
        else
            printf("This value is not in the tree!\n");
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
