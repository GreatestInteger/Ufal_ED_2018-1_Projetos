
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

node* create_priority_queue()
{
    node* new_pq = (node*) malloc(sizeof(node));
    new_pq = NULL;

    return new_pq;
}

int is_empty(node *pq)
{
    return (pq == NULL);
}

node *insert_node(node *pq, node *new_node)
{

    if (pq == new_node)
    {
		new_node -> next = NULL;

        return new_node;
    }
    else if((is_empty(pq)) || (new_node -> frequency > pq -> frequency))
    {
        new_node -> next = pq;

        return new_node;
    }
    else
    {
        node* current = pq;
        while((current -> next != NULL) && (current -> next -> frequency > new_node -> frequency))
        {
            current = current -> next;
        }
        new_node -> next = current -> next;
        current -> next = new_node;

        return pq;
    }
}

node *enqueue(node *pq, void *i, int p)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = i;
    new_node -> frequency = p;
    new_node -> left = NULL;
    new_node -> right = NULL;

    pq = insert_node(pq, new_node);

    return pq;
}

node *merge(node *pq)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> left = pq;
    new_node -> right = pq -> next;
    unsigned char data = '*';
    unsigned char *data_p = &data;
    printf("merge unsigned char data [%c]\n", data);

    if(new_node -> right -> next != NULL)
    {
        pq = new_node -> right -> next;
    }
    else
    {
        pq = new_node;
    }
    new_node -> left -> next = NULL;
    new_node -> right -> next = NULL;
    new_node -> item = data_p; // Verificar depois
    printf("merge new_node -> item [%c]\n", *(unsigned char*)new_node -> item);
    new_node -> frequency = (new_node -> left -> frequency) + (new_node -> right -> frequency);

    pq = insert_node(pq, new_node);

    return pq;
}

node *huff_tree(node *pq)
{
    unsigned char data1 = '*';
    unsigned char *data_p1 = &data1;
    printf("huff_tree unsigned char data [%c]\n", data1);
    if(pq -> next == NULL)
    {
        printf("Entrou\n");
        node* new_node = (node*) malloc(sizeof(node));

        new_node -> item = data_p1;// Verificar depois também
        printf("huff_tree new_node -> item [%c]\n", *(unsigned char*)new_node -> item);
        new_node -> left = pq;
        new_node -> right = NULL;
        new_node -> frequency = pq -> frequency;
        pq = new_node;
    }
    else
    {
        while(pq -> next != NULL)
        {
            pq = merge(pq);
        }
    }
    return pq;
}

void print_tree(node *pq){

    //printf("Entrou\n");
    if (pq != NULL) {

        //printf("IF pq != NULL\n");

        printf ("[%c]", *(unsigned char*) pq -> item);
        print_tree (pq -> left);
        print_tree (pq -> right);
    }

}

void print_priority_queue(node *pq)
{
    if(is_empty(pq))
    {
        printf("It is empty.\n");
    }
    else {
        printf("---- \n");

        node * aux = pq;
        while (pq != NULL) {
            printf("[%p][%c]\n", pq->item, *(unsigned char*) pq->item);
            printf("[%p][%d]\n", pq->frequency, pq->frequency);
            pq = pq->next;
        }
        pq = aux;
        printf("---- \n");
    }
}

int main () {

    node* test = create_priority_queue();

    unsigned char item = 'c';
    unsigned char item2 = 'b';
    unsigned char item3 = 'x';
    unsigned char item4 = 'f';
    unsigned char item5 = 'z';

    test = enqueue(test, &item, 5);

    test = enqueue(test, &item2, 10);

    test = enqueue(test, &item3, 7);

    test = enqueue(test, &item4, 1000000);

    test = enqueue(test, &item5, 1);

    //print_priority_queue(test);

    test = huff_tree(test);

    //printf("[%d]\n", is_empty(test));

    print_tree(test);

    return 0;
}
