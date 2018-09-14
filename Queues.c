//IMPLEMENTAÇÃO DE FILAS DE PRIORIDADE

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

int dequeue(priority_queue *pq)
{
    if(is_empty(pq))
    {
        printf("Priority Queue Underflow\n");
        return NULL;
    }
    else
    {
        node *node = pq -> head;
        pq -> head = pq -> head -> next;
        node -> next = NULL;
        return node -> item;
    }
}

int maximum(priority_queue *pq)
{
    if(is_empty(pq))
    {
        printf("Priority Queue Underflow\n");
        return -1;
    }
    else
    {
        return pq -> head -> item;
    }
}



//---------------------------------------------------------//
