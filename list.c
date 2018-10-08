#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    int item;
    node *next;
};

node* create_linked_list()
{
    return NULL;
}

int is_empty(node *head)
{
    return (head == NULL);
}

node *add_list(node *head, int item)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = item;
    new_node -> next = head;
    return new_node;
}


void print_linked_list(node *head)
{
    while(head != NULL)
    {
        printf("%d ", head -> item);
        head = head -> next;
    }
}

int search_list(node *head, int item)
{
    int cont = 0;
    while(head != NULL)
    {
      cont++;
        if(head -> item == item)
        {
            return cont;
        }
        head = head -> next;
    }
    return -1;
}

void free_node(node **head){

	if (*head != NULL){

		free_node(&(*head)->next);
		free(*head);
		*head = NULL;
	}
}
