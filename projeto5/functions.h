typedef struct tree{
    int value;
    struct tree *right;
    struct tree *left;
}tree;

FILE* openArchive(char *);
int readNumbers(FILE *);
tree* createNewNode(int);
tree* insert(tree *, tree *);
tree* loadTreeFromFile(char *);
void print(tree *, int);
void showTree(tree *);
int checksIsFull(tree *);
void isFull(tree *);
void searchValue(tree *, int);
int getHeight(tree *);
void removeValue(tree *, int);
void printInOrder(tree *);
void printPreOrder(tree *);
void printPostOrder(tree *);
void balanceTree(tree *);
void menu();
