#include "BinarySearchTree.h"
#include "Lista.h"

int main() {
    int i;
    FILE* arquivo_temp = fopen("testando.csv","w");
    fprintf(arquivo_temp,"%s\n","N_ELEMENTS,List,ABB");
    Tree* BinarySearchTree = createEmptyTree();
    node* List = createEmptyList();

    printf("digite a quantidade de elementos para as estruturas: ");
    scanf("%d",&i);
    int ale_num,cont;
    for(cont = 1; cont <= i; cont++) {
        ale_num = rand() % i + 1;
        BinarySearchTree = insertNodeTree(BinarySearchTree, ale_num);
        insertNode(&List, ale_num);
        fprintf(arquivo_temp,"%d, %d, %d\n",cont,search_list(List,ale_num),binarySearch(BinarySearchTree,ale_num));
    }

    fclose(arquivo_temp);
    printf("Concluido\n");

    free_node(&List);
    return 0;
}
