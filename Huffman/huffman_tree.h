#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    void *item;
    int frequency;
    node* next;
    node* left;
    node* right;
};

int is_empty(node *pq);

node *insert_node(node *pq, node *new_node);

node *enqueue(node *pq, void *data, int freq);

node *merge(node *pq);

node *huff_tree(node *pq);

int is_leaf(node *pq);
