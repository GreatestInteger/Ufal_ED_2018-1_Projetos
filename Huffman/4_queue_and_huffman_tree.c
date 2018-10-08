typedef struct node node;

struct node{
    void *item;
    int frequency;
    node* next;
    node* left;
    node* right;
};

node *create_empty_queue(){

    return NULL;
}

node *create_empty_tree(){

	return NULL;
}

unsigned char character = '*'; // Global variable

int is_empty(node *pq)
{
    return (pq == NULL);
}

node *insert_node(node *pq, node *new_node)
{

    if (pq == NULL)
    {
        return new_node;
    }
    else if(new_node->frequency <= pq->frequency)
    {
        new_node->next = pq;

        return new_node;
    }
    else
    {
        node* current = pq;
        while((current->next != NULL) && (current->next->frequency < new_node->frequency))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;

        return pq;
    }
}

node *enqueue(node *pq, void *data, int freq)
{

    unsigned char *new_node_unsigned_char = (unsigned char*) malloc(sizeof(unsigned char));

    *new_node_unsigned_char = *(unsigned char*) data;

    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = new_node_unsigned_char;
    new_node->frequency = freq;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    pq = insert_node(pq, new_node);

    return pq;
}

node *merge(node *pq)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = &character;
    new_node->frequency = (pq->frequency) + (pq->next->frequency);
    new_node->next = NULL;
    new_node->left = pq;
    new_node->right = pq->next;

    if(new_node->right->next != NULL) // If there are more then two nodes in the priority queue
    {
        pq = new_node->right->next;

        new_node->left->next = NULL;
        new_node->right->next = NULL;

        pq = insert_node(pq, new_node);
    }
    else // When there are only two nodes in the priority queue. Last transformation/merge.
    {
        pq = new_node;
    }

    return pq;
}

node *huff_tree(node *pq)
{

    if(pq->next == NULL) // If the queue contains only one node
    {

        node* new_node = (node*) malloc(sizeof(node));

        new_node->item = &character;

        new_node->frequency = pq->frequency;

        new_node->next = NULL;
        new_node->left = pq;
        new_node->right = NULL;

        pq = new_node;
    }
    else // The queue contains more then one node
    {

        while(pq->next != NULL)
        {
            pq = merge(pq);
        }
    }
    return pq;
}

int is_leaf(node *pq){

    return ((pq->left == NULL)&&(pq->right == NULL));

}

int size_huff(node *huff){

	if(huff == NULL){
		return 0;
	}
    else{
		return 1 + size_huff(huff->left) + size_huff(huff->right);
	}
}

void print_tree_with_node_atributes(node *pq){

    printf("\n");
    if (pq != NULL) {

        //printf("IF pq != NULL\n");

        printf("Node:\n\taddress[%p]\n\titem[%c]\n\tfrequency[%d]\n\tnext[%p]\n\tleft[%p]\n\tright[%p]\n\n", pq,*(unsigned char*) pq->item, pq->frequency, pq->next, pq->left, pq->right);
        print_tree_with_node_atributes (pq->left);
        print_tree_with_node_atributes (pq->right);
    }

}

void print_tree_prison(node *pq){

    //printf("Entrou\n");
    if (pq != NULL) {
        printf("[%c]", *(unsigned char*) pq->item);
        print_tree_prison (pq->left);
        print_tree_prison (pq->right);
    }

}

void print_tree(node *pq){

    //printf("Entrou\n");
    if (pq != NULL) {
        printf("%c", *(unsigned char*) pq->item);
        print_tree (pq->left);
        print_tree (pq->right);
    }

}

void print_priority_queue(node *pq)
{
    if(is_empty(pq))
    {
        printf("It is empty.\n");
    }
    else {
        printf("print_priority_queue ---- Start\n");

        node* current = pq;
        while (current != NULL) {
            printf("Node:\n\taddress[%p]\n\titem[%c]\n\tfrequency[%d]\n\tnext[%p]\n\tleft[%p]\n\tright[%p]\n", current,*(unsigned char*) current->item, current->frequency, current->next, current->left, current->right);

            current = current->next;
        }

        printf("print_priority_queue ---- End\n");
    }
}
