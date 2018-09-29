//IMPLEMENTAÇÃO DE FILAS DE PRIORIDADE
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct priority_queue priority_queue;

struct node{
  void *item;
  int priority;
  node* next;
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

void enqueue(priority_queue *pq, void *i, int p)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = i;
    new_node -> priority = p;
    if((is_empty(pq)) || (p > pq -> head -> priority))
    {
        new_node -> next = pq -> head;
        pq -> head = new_node;
    }
    else
    {
        node* current = pq -> head;
        while((current -> next != NULL) && (current -> next -> priority > p))
        {
            current = current -> next;
        }
        new_node -> next = current -> next;
        current -> next = new_node;
    }
}

int dequeue_integers(priority_queue *pq)
{
    int value;

    printf("Is empty (inside dequeue_integers): [%d]\n", is_empty(pq));

    if(is_empty(pq))
    {
        printf("Priority Queue Underflow\n");
        return -1;
    }
    else
    {
        node *node = pq -> head;
        pq -> head = pq -> head -> next;
        node -> next = NULL;
        value = *(int*) node -> item;
        free(node);
        return value;
    }
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

//---------------------------------------------------------//

int main () {

  int item = 42, item_2 = 50, item_3 = 37;
  printf("[%p][%d]\n", &item, item);
  printf("[%p][%d]\n", &item_2, item_2);
  printf("[%p][%d]\n", &item_3, item_3);

  priority_queue *pqueue = create_priority_queue();

  printf("Is empty (after creating pqueue): [%d]\n", is_empty(pqueue));

  enqueue(pqueue, &item, 100);
  enqueue(pqueue, &item_2, 9);
  enqueue(pqueue, &item_3, 77);

  printf("Is empty (after enqueue): [%d]\n", is_empty(pqueue));

  print_priority_queue_of_integers(pqueue);

  printf("%d\n", dequeue_integers(pqueue));
  printf("%d\n", dequeue_integers(pqueue));
  printf("%d\n", dequeue_integers(pqueue));
  printf("%d\n", dequeue_integers(pqueue));
  print_priority_queue_of_integers(pqueue);

  return 0;
}
