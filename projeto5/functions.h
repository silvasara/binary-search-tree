typedef struct tree{
    int value;
    struct tree *left;
    struct tree *right;
} tree;

tree *createsNew(int value);
tree *loadTreeFromFile(char *archive_name);
void showTree(tree *t);
void isFull(tree *t);
void searchValue(tree *t, int value);
void getHeight(tree *t);
void removeValue(tree *t, int value);
void printInOrder(tree *t);
void printPreOrder(tree *t);
void printPosOrder(tree *t);
void balanceTree(tree *t);
void menu();
