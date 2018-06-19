#include <stdio_ext.h>
#include "functions.c"

int main() {
    int option;
    char userFileName[100], *fileName;
    tree *root = NULL;

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
                root = loadTreeFromFile(fileName);

                free(fileName);

                break;

            case 2:
                system("clear");
                showTree(root);
                break;

            case 3:
                system("clear");
                isFull(root);
                break;

            case 4:
                system("clear");
                printf("Enter the value you would like to search: ");
                int value;
                scanf("%d", &value);
                searchValue(root, value);
                break;

            case 5:
                system("clear");
                getHeight(root);
                break;

            case 6:
                system("clear");
                printf("Enter the value you would like to delete: ");
                int valueD;
                scanf("%d", &valueD);
                getchar();
                root = removeValue(root, valueD);
                break;

            case 7:
                system("clear");
                printInOrder(root);
                break;

            case 8:
                system("clear");
                printPreOrder(root);
                break;

            case 9:
                system("clear");
                printPostOrder(root);
                break;

            case 10:
                system("clear");
                balanceTree(root);
                break;
        }
    }
    while(option != 0);
    return 0;
}
