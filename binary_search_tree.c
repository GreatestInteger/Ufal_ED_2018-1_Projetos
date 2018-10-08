#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct binary_tree binary_tree;

struct binary_tree{
  int item;
  binary_tree *left;
  binary_tree *right;
};

binary_tree* create_empty_binary_tree()
{
  return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right)
{
  binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
  new_binary_tree->item = item;
  new_binary_tree->left = left;
  new_binary_tree->right = right;
  return new_binary_tree;
}

binary_tree* add_btree(binary_tree *bt, int item)
{
  if(bt == NULL)
  {
    bt = create_binary_tree(item, NULL, NULL);
  }
  else if(bt->item > item)
  {
    bt->left = add_btree(bt->left, item);
  }
  else
  {
    bt->right = add_btree(bt->right, item);
  }
  return bt;
}

int search_btree(binary_tree *bt, int item){
  int op = 0;
  binary_tree *temp;
  temp = bt;
  while (temp != NULL) {
      op++;
      if (temp->item == item){
          return op;
      }
      if (temp->item > item)
          temp = temp->left;
      else
          temp = temp->right;
  }
  return -1;
}

void pre_order(binary_tree *bt) {
    if(bt != NULL) {
        printf("[%d] ", bt->item);
        pre_order(bt->left);
        pre_order(bt->right);
    }
}
