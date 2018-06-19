typedef struct tree{
    int value;
    struct tree *right;
    struct tree *left;
}tree;

typedef struct BST {
    struct BST *left, *right;
    int branch;
    int height;
    int element;
    int type;
    char label[11];
}BST;

FILE* openArchive(char *);
int readNumbers(FILE *);
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
bool checksIsFull(tree *);
void isFull(tree *);
void searchValue(tree *, int);
int calculateHeight(tree *);
void getHeight(tree *);
tree *removeValue(tree *, int);
tree *removeRoot(tree *);
tree *verifyType(tree *, tree *);
tree *findSuccessor(tree *);
void printInOrder(tree *);
void printPreOrder(tree *);
void printPostOrder(tree *);
int getBalanceFactor(tree *);
tree *rotateRight(tree *t);
tree *rotateLeft(tree *t);
tree *rotateLeftRight(tree *t);
tree *rotateRightLeft(tree *t);
tree *balance(tree *t, tree *root);
void balanceTree(tree *);
void menu();
