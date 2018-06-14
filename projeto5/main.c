#include "functions.c"

int main(){
    tree *t = loadTreeFromFile("./BSTs/bst1.txt");

    printInOrder(t);

    return 0;
}
