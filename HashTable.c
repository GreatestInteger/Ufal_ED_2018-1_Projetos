/* HASH TABLE COMO VISTO NOS SLIDES */

#include <stdio.h>
#include <stdlib.h>
/*
hash_table* create_hash_table();
void put(hash_table *ht, int key, int value);
int get(hash_table *ht, int key);
void remove(hash_table *ht, int key);
int contains_key(hash_table *ht, int key);
void print_hash_table(hash_table *ht);
*/
typedef struct element element;
typedef struct hash_table hash_table;

struct element {
    int key;
    int value;
};
// ========================================== //
struct hash_table {
    element *table[256]; // Vector of pointers
};
// ========================================== //
hash_table* create_hash_table()
{
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for (i = 0; i < 256; i++) {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}
// ========================================== //
void put(hash_table *ht, int key, int value)
{
    int h = key % 256;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            ht->table[h]->value = value;
            break;
        }
        h = (h + 1) % 256;
    }
    if (ht->table[h] == NULL) {
        element *new_element =
        (element*) malloc(sizeof(element));
        new_element->key = key;
        new_element->value = value;
        ht->table[h] = new_element;
    }
}
// ========================================== //
int get(hash_table *ht, int key)
{
    int h = key % 256;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            return ht->table[h]->value;
        }
        h = (h + 1) % 256;
    }
    return -100;
}
// ========================================== //
void remove_wrong(hash_table *ht, int key)
{
    int h = key % 256;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            free(ht->table[h]);
            ht->table[h] = NULL;
        }
        h = (h + 1) % 256;
    }
}
// ========================================== //
void remove_element(hash_table *ht, int key)
{
    int h = key % 256;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            ht->table[h]->key = -1;
        }
        h = (h + 1) % 256;
    }
}
// ========================================== //
void print_hash_table(hash_table *ht) {

    int i = 0;
    printf("ht: [%p]\n", ht);
    for (i = 0; i < 256; i++) {

        if (ht->table[i] == NULL){
            printf("i: %d, ht->table: %p\n", i, ht->table[i]);
        }
        else {
            printf("i: %d, ht->table: %p, ht->table[%d]->key: %d, ht->table[%d]->value: %d\n", i, ht->table[i], i, ht->table[i]->key, i, ht->table[i]->value);
        }
    }
}
// ========================================== //
int main () {

    hash_table *ht = create_hash_table();
    put(ht, 3, 1000);
    print_hash_table(ht);
    put(ht, 14, 2000);
    print_hash_table(ht);
    put(ht, 15, 3000);
    print_hash_table(ht);
    put(ht, 92, 4000);
    print_hash_table(ht);

    printf("Get 92: [%d]\n", get(ht, 92));
    printf("Get 16: [%d]\n", get(ht, 16));

    remove_element(ht, 15);
    print_hash_table(ht);

    printf("Get 92: [%d]\n", get(ht, 92));

    put(ht, 16, 4000);
    //print_hash_table(ht);
    put(ht, 17, 4000);
    //print_hash_table(ht);
    put(ht, 18, 4000);
    //print_hash_table(ht);
    put(ht, 19, 4000);
    //print_hash_table(ht);
    put(ht, 20, 4000);
    //print_hash_table(ht);
    put(ht, 21, 4000);
    //print_hash_table(ht);
    put(ht, 22, 4000);
    print_hash_table(ht);

}
