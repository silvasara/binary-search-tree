#include <stdio_ext.h>
#include "functions.c"

int main() {
    int option;
    char userFileName[100], *fileName;
    tree *raiz = NULL;

    do{
        menu();
        scanf("%d", &option);
        switch(option){
            case 1:
                printf("Enter the name of the file: ");
                __fpurge(stdin);
                fgets(userFileName, 100, stdin);
                int size = strlen(userFileName);
                fileName = calloc((size-1), sizeof(char));
                strncpy(fileName, userFileName, (size-1));
                raiz = loadTreeFromFile(fileName);

                free(fileName);

                break;

            case 2:
                system("clear");
                showTree(raiz);
                break;

            case 3:
                system("clear");
                isFull(raiz);
              //(isFull(raiz) == 1){
              //    printf("Tree is full");
              //}
              //else{
              //    printf("Tree is not full");
              //}
                break;

            case 4:
                system("clear");
                printf("Enter the value you would like to search: ");
                int value;
                scanf("%d", &value);
                searchValue(raiz, value);
                break;

            case 5:
                system("clear");
                printf("Tree height: %d", getHeight(raiz));
                break;

            case 6:
                system("clear");
                printf("Enter the value you would like to delete: ");
                int valueD;
                scanf("%d", &valueD);
                removeValue(raiz, valueD);
                break;

            case 7:
                system("clear");
                printInOrder(raiz);
                break;

            case 8:
                system("clear");
                printPreOrder(raiz);
                break;

            case 9:
                system("clear");
                printPostOrder(raiz);
                break;

            case 10:
                system("clear");
                balanceTree(raiz);
                break;
        }
    }while(option != 0);

    return 0;
}
