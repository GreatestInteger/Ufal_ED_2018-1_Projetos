
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct priority_queue priority_queue;

struct node{
    void *item;
    int frequency;
    node* next;
    node* left;
    node* right;
};

struct priority_queue
{
    node* head;
};

priority_queue* create_priority_queue()
{
    priority_queue* new_pq = (priority_queue*) malloc(sizeof(priority_queue));
    new_pq -> head = NULL;
    return new_pq;
}

int is_empty(priority_queue *pq)
{
    return (pq -> head == NULL);
}

priority_queue *insert_node(priority_queue *pq, node *new_node)
{
    if((is_empty(pq)) || (new_node -> frequency > pq -> head -> frequency)) // BUG!?
    {
        new_node -> next = pq -> head;
        return new_node;
    }
    else
    {
        node* current = pq -> head;
        while((current -> next != NULL) && (current -> next -> frequency > new_node -> frequency))
        {
            current = current -> next;
        }
        new_node -> next = current -> next;
        current -> next = new_node;
        return pq;
    }
}

priority_queue *enqueue(priority_queue *pq, void *i, int p)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = i;
    new_node -> frequency = p;
    new_node -> left = NULL;
    new_node -> right = NULL;
    pq = insert_node(pq, new_node);
    return pq;
}

priority_queue *merge(priority_queue *pq)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> left = pq -> head;
    new_node -> right = pq -> head -> next;
    if(new_node -> right -> next != NULL)
    {
        pq -> head = new_node -> right -> next;
    }
    else
    {
        pq -> head = new_node;
    }
    new_node -> left -> next = NULL;
    new_node -> right -> next = NULL;
    new_node -> item = *(unsigned char*)'*'; // Verificar depois
    new_node -> frequency = (new_node -> left -> frequency) + (new_node -> right -> frequency);
    pq = insert_node(pq, new_node);
    return pq;
}

void print_priority_queue_of_integers(priority_queue *pq)
{
    if(is_empty(pq))
    {
        printf("It is empty.\n");
    }
    else {
        printf("---- \n");

        node * aux = pq->head;
        while (pq -> head != NULL) {
            printf("[%p][%d]\n", pq->head->item, *((int*) pq->head->item));
            pq->head = pq->head->next;
        }
        pq->head = aux;
        printf("---- \n");
    }
}
