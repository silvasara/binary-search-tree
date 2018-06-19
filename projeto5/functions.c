#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int left[MAX_HEIGHT];
int right[MAX_HEIGHT];
int space = 3;
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
        printf("Can not open file!\n");
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

    sprintf(node->label, "   %d", t->value);
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
    int ttLeft = (node->type != -1);
    right[y] = MAX(right[y], x + ((node->element - ttLeft) / 2));

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

    if (node->right == NULL && node->left == NULL)
        node->branch = 0;

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
            delta = MAX(delta, space + 1 + right[i] - left[i]);

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
            printf(" /");
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

bool checkisFull(tree* root){ //default bool: false
    // árvore é vazia
    if (root == NULL)
        return true;

    // nó da folha
    if (root->left == NULL && root->right == NULL)
        return true;

    // se left e right não forem NULL, e left e right tiverem filhos
    if ((root->left) && (root->right))
        return (checkisFull(root->left) && checkisFull(root->right));

    //nenhuma das condições
    return false;
}

void isFull(tree* root){

    if(checkisFull(root))
        printf("The tree is full.\n");
    else
        printf("The tree is not full.\n");
}

void searchValue(tree *root, int value){
    int level;
    if (root != NULL){
        if(value == root->value){
            printf("Root node\n");
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

int calculateHeight(tree *root){
    int leftH, rightH, height;

    if (root == NULL)
        return 0;

    leftH = calculateHeight(root->left);
    rightH = calculateHeight(root->right);
    height = leftH > rightH ? leftH + 1 : rightH + 1;

    return height;
}

void getHeight(tree *root){
    if(calculateHeight(root) == 0)
        printf("Tree is empty\n");
    else
        printf("Tree height: %d\n", calculateHeight(root));
}

tree *removeValue(tree *root, int value){
    tree *dad = NULL, *aux = root;
    while (aux != NULL){
        if (aux->value == value){
            break;
        }

        dad = aux;
        if (aux->value < value){
            aux = dad->right;
        }

        else{
            aux = dad->left;
        }
    }

    if (aux == NULL){
        printf("This value does not belong in this tree.\n");
    }

    else{
        if (dad == NULL){
            root = removeRoot(root);
        }

        else{
            aux = verifyType(aux,dad);
            free(aux);
        }
        printf("\nThe value has been removed.\n\n");
    }
    return root;
}

tree *removeRoot(tree *root){
    tree *aux;
    if (root->right != NULL || root->left != NULL)
    {
        if (root->right != NULL && root->left != NULL)
        {
            aux = findSuccessor(root);
            free(aux);
            return root;
        }
        else
        {
            if (root->right != NULL)
            {
                aux = root->right;
                free(root);
                return aux;
            }
            else
            {
                aux = root->left;
                free(root);
                return aux;
            }
        }
    }
    else
    {
        free(root);
        return NULL;
    }
}

tree *verifyType(tree *root, tree *dad){
    if (root->right != NULL || root->left != NULL)
    {
        if (root->right != NULL && root->left != NULL)
        {
            return findSuccessor(root);
        }
        else
        {
            if (root->right != NULL)
            {
                if (dad->right == root)
                {
                    dad->right = root->right;
                    return root;
                }
                else
                {
                    dad->left = root->right;
                    return root;
                }
            }
            else
            {
                if (dad->right == root)
                {
                    dad->right = root->left;
                    return root;
                }
                else
                {
                    dad->left = root->left;
                    return root;
                }
            }
        }
    }
    else
    {
        if (dad->value < root->value)
        {
            dad->right = NULL;
        }
        else
        {
            dad->left = NULL;
        }
        return root;
    }
}

tree *findSuccessor(tree *root){
    tree *successor, *dad, *aux;
    int value;
    successor = root->right;
    dad = root;
    while (successor->left != NULL)
    {
        dad = successor;
        successor = dad->left;
    }
    value = successor->value;
    aux = verifyType(successor,dad);
    root->value = value;
    return aux;
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

int getBalanceFactor(tree *t){
    int factor = 0;

    if(t->left)
        factor += calculateHeight(t->left);
    if(t->right)
        factor -= calculateHeight(t->right);

    return factor;
}

tree *rotateRight(tree *t){
    tree *a = t;
    tree *b = a->left;

    a->left = b->right;
    b->right = a;

    return b;
}

tree *rotateLeft(tree *t){
    tree *a = t;
    tree *b = a->right;

    a->right = b->left;
    b->left = a;

    return b;
}

tree *rotateLeftRight(tree *t){
    tree *a = t;
    tree *b = a->left;
    tree *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    return c;
}

tree *rotateRightLeft(tree *t){
    tree *a = t;
    tree *b = a->right;
    tree *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    return c;
}

tree *balance(tree *t){
    tree *aux = NULL;

    if(t->left)
        t->left  = balance(t->left);

    if(t->right)
        t->right = balance(t->right);

    int factor = getBalanceFactor(t);

    if(factor >= 2){
        if(getBalanceFactor(t->left) <= -1)
            aux = rotateLeftRight(t);

        else
            aux = rotateRight(t);
    }
    else if(factor <= -2){
        if(getBalanceFactor(t->right) >= 1)
            aux = rotateRightLeft(t);
        else
            aux = rotateLeft(t);
    }
    else
        aux = t;

    return aux;
}

int checkIsBalanced(tree *root) {
    if (root == NULL)
        return 2;

    int value = abs(calculateHeight(root->left) - calculateHeight(root->right)) <= 1;
    if(checkIsBalanced(root->left) == 0 && checkIsBalanced(root->right) == 0)
        value = 0;

    return value;
}

tree *balanceTree(tree *root){
    tree *aux = NULL;

    if (checkIsBalanced(root) == 0){
        aux = balance(root);
        if(aux != root)
            root = aux;
    }
    else if(checkIsBalanced(root) == 1)
        printf("Tree is already balanced\n");

    return root;
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
