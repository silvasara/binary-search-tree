typedef struct tree{
    int value;
    struct tree *right;
    struct tree *left;
}tree;

typedef struct BST {
    struct BST *left, *right;
    int branch;      //length of the branch from this node to its children
    int height;
    int element;
    int type;        // -1 if is left, 0 if is root, 1 if right
    char label[11];
}BST;

FILE* openArchive(char *);
void readNumbers(FILE *, int *);
tree* createNewNode(int);
tree* insert(tree *, tree *);
tree *loadTreeFromFile(char *);
BST *createsBSTRecursive(tree *t);
void getLeft(BST *, int , int );
void getRight(BST *node, int , int);
void fillBranch(BST *);
void printLevel(BST *, int , int);
void freeBST(BST *);
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
