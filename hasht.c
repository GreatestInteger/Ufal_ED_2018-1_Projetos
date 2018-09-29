#include "huffman_tree.c"

typedef struct element element;
typedef struct hash_table hash_table;

#define SIZE_ASCII 256

struct element{
    int frequency;
    char bits[SIZE_ASCII];//VERIFICAR
};

struct hash_table{
    element *table[SIZE_ASCII];
};

hash_table *create_hash_table(){
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for(i = 0; i < SIZE_ASCII; i++){

        new_hash_table->table[i] = (element*) malloc(sizeof(element));
        new_hash_table->table[i]->frequency = 0;
    }
    return new_hash_table;
}

void pass_through_edges_and_add_characters(node *huffman_tree, unsigned char *bit_string, int index, unsigned char bit, hash_table *ht) {

    if(index > 1){
      bit_string[index] = bit;
      if(is_leaf(huffman_tree))
      {
        bit_string[index + 1] = '\0';
        strcpy(ht->table[(int) *(unsigned char*) huffman_tree->item]->bits, bit_string); //VERIFICAR
      }
    }

    if(tree->left != NULL){
      pass_through_edges_and_add_characters(huffman_tree, bit_string, index + 1, '0', ht);
    }

    if(tree->right != NULL){
      pass_through_edges_and_add_characters(huffman_tree, bit_string, index + 1, '1', ht);
    }

}
