#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int left[MAX_HEIGHT];
int right[MAX_HEIGHT];
int gap = 3;
int printNext;

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
        rewind(archive);
        for(int i = 0 ; i<totalOfNumbersInFile;i++){
            fscanf(archive, "%d ", &fileNumbers[i]);
        }
        fclose(archive);
        for(int i = 0; i < totalOfNumbersInFile; i++){
            new = createsNew(fileNumbers[i]);
            root = insert(root, new);
            printf("%d\n", fileNumbers[i] );
        }
    }

    return root;
}

BST *createsBSTRecursive(tree *t) {
    BST *node;
    if (t == NULL)
        return NULL;

    node = malloc(sizeof(BST));
    node->left = createsBSTRecursive(t->left);
    node->right = createsBSTRecursive(t->right);
    node->type = 0;

    if (node->left != NULL)
        node->left->type = -1;
    if (node->right != NULL)
        node->right->type = 1;

    sprintf(node->label, "%d", t->value);
    node->element = strlen(node->label);

    return node;
}

void getLeft(BST *node, int x, int y) {
    if (node == NULL)
        return;

    int isLeft = (node->type == -1);
    left[y] = MIN(left[y], x - ((node->element - isLeft) / 2));

    if (node->left != NULL) {
        for(int i = 1; i <= node->branch  && y + i < MAX_HEIGHT; i++) {
            left[y + i] = MIN(left[y + i], x - i);
        }
    }

    getLeft(node->left, x - node->branch - 1, y + node->branch + 1);
    getLeft(node->right, x + node->branch + 1, y + node->branch + 1);
}

void getRight(BST *node, int x, int y) {
    if (node == NULL)
        return;
    int notLeft = (node->type != -1);
    right[y] = MAX(right[y], x + ((node->element - notLeft) / 2));

    if (node->right != NULL) {
        for(int i = 1; i <= node->branch && y + i < MAX_HEIGHT; i++) {
            right[y + i] = MAX(right[y + i], x + i);
        }
    }

    getRight(node->left, x - node->branch - 1, y + node->branch + 1);
    getRight(node->right, x + node->branch + 1, y + node->branch + 1);
}

void fillBranch(BST *node) {
    int heightMin, delta;

    if (node == NULL)
        return;

    fillBranch(node->left);
    fillBranch(node->right);

    if (node->right == NULL && node->left == NULL) {
        node->branch = 0;
    }
    else {
        if (node->left != NULL) {
            for (int i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
                right[i] = -INFINITY;

            getRight(node->left, 0, 0);
            heightMin = node->left->height;
        }
        else
            heightMin = 0;
        if (node->right != NULL) {
            for (int i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
                left[i] = INFINITY;

            getLeft(node->right, 0, 0);
            heightMin = MIN(node->right->height, heightMin);
        }
        else
            heightMin = 0;

        delta = 4;
        for (int i = 0; i < heightMin; i++)
            delta = MAX(delta, gap + 1 + right[i] - left[i]);

        if (((node->left != NULL && node->left->height == 1) ||
                    (node->right != NULL && node->right->height == 1)) && delta > 4) {
            delta--;
        }

        node->branch = ((delta + 1) / 2) - 1;
    }

    int height = 1;
    if (node->left != NULL) {
        height = MAX(node->left->height + node->branch + 1, height);
    }
    if (node->right != NULL) {
        height = MAX(node->right->height + node->branch + 1, height);
    }
    node->height = height;
}

void printLevel(BST *node, int x, int level) {
    if (node == NULL) return;
    int isleft = (node->type == -1);
    if (level == 0) {
        int i;
        for (i = 0; i < (x - printNext - ((node->element - isleft) / 2)); i++)
            printf(" ");

        printNext += i;
        printf("%s", node->label);
        printNext += node->element;
    }
    else if (node->branch >= level) {
        if (node->left != NULL) {
            int i;
            for (i = 0; i < (x - printNext - (level)); i++)
                printf(" ");

            printNext += i;
            printf("/");
            printNext++;
        }
        if (node->right != NULL) {
            int i;
            for (i = 0; i < (x - printNext + (level)); i++)
                printf(" ");

            printNext += i;
            printf("\\");
            printNext++;
        }
    }
    else {
        printLevel(node->left, x - node->branch - 1, level - node->branch - 1);
        printLevel(node->right, x + node->branch + 1, level - node->branch - 1);
    }
}

void freeBST(BST *node) {
    if (node == NULL) return;
    freeBST(node->left);
    freeBST(node->right);
    free(node);
}

void showTree(tree *t) {
    BST *proot;

    if (t == NULL)
        return;
    proot = createsBSTRecursive(t);
    fillBranch(proot);

    for (int i = 0; i < proot->height && i < MAX_HEIGHT; i++)
        left[i] = INFINITY;

    getLeft(proot, 0, 0);
    int xmin = 0;

    for (int i = 0; i < proot->height && i < MAX_HEIGHT; i++)
        xmin = MIN(xmin, left[i]);
    for (int i = 0; i < proot->height; i++) {
        printNext = 0;
        printLevel(proot, -xmin, i);
        printf("\n");
    }

    freeBST(proot);
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
        printf("tree is full!\n");
    else if(checksIsFull == 0)
        printf("tree is empty!\n");
    else
        printf("tree is not full\n");
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
