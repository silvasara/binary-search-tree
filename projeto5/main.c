#include <stdio_ext.h>
#include "functions.c"

int main(int argc, char *argv[]) {

    int option, tamanho, valueSearched, valueDeleted;
    char userFileName[100], *fileName;
    tree *raiz = NULL;

    do{
        menu();
        scanf("%d", &option);
        switch(option){
            case 1:
                LIMPA_TELA;

                printf("Enter the name of the file: ");
                __fpurge(stdin);
                fgets(userFileName, 100, stdin);
                tamanho = strlen(userFileName);
                fileName = calloc((tamanho-1), sizeof(char));
                strncpy(fileName, userFileName, (tamanho-1));
                printf("fileName %s", fileName);
                raiz = loadTreeFromFile(fileName);

                free(fileName);

                break;

            case 2:
                LIMPA_TELA;
                showTree(raiz);
                break;

            case 3:
                LIMPA_TELA;
                if(isFull(raiz) == 1){
                    printf("Tree is full");
                }
                else{
                    printf("Tree is not full");
                }
                break;

            case 4:
                LIMPA_TELA;
                printf("Enter the value you would like to search: ");
                scanf("%d", &valueSearched);
                searchValue(raiz, valueSearched);
                break;

            case 5:
                LIMPA_TELA;
                printf("Tree height: %d", getHeight(raiz));
                break;

            case 6:
                LIMPA_TELA;
                printf("Enter the value you would like to delete: ");
                scanf("%d", &valueDeleted);
                removeValue(raiz, valueDeleted);
                break;

            case 7:
                LIMPA_TELA;
                printInOrder(raiz);
                break;

            case 8:
                LIMPA_TELA;
                printPreOrder(raiz);
                break;

            case 9:
                LIMPA_TELA;
                printPostOrder(raiz);
                break;

            case 10:
                LIMPA_TELA;
                balanceTree(raiz);
                break;
        }
    }while(option != 0);

    return 0;
}
