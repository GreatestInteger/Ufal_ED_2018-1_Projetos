#include "binary_search_tree.c"
#include "list.c"

int main() {
    int i;
    FILE* arquivo_temp = fopen("testando.txt","w");
    fprintf(arquivo_temp,"%s\n","N_ELEMENTS,List,ABB");
    binary_tree* BinarySearchTree = create_empty_binary_tree();
    node* List = create_linked_list();

    printf("digite a quantidade de elementos para as estruturas: ");
    scanf("%d",&i);
    int ale_num,cont;
    for(cont = 1; cont <= i; cont++) {
        ale_num = rand() % i + 1;
        BinarySearchTree = add_btree(BinarySearchTree, ale_num);
        List = add_list(List, ale_num);
        fprintf(arquivo_temp,"%d\n%d\n%d\n",cont,search_list(List, ale_num),search_btree(BinarySearchTree, ale_num));
    }

    fclose(arquivo_temp);
    printf("Concluido\n");

    free_node(&List);
    return 0;
}
