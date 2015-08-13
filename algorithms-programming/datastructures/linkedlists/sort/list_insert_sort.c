/*

Given a linked list which is sorted, how will you insert in sorted way

*/

void insertSort(struct node **head, int elem)
{
        struct node *temp;

        temp = (struct node*) malloc (sizeof(node));
        temp->next = NULL;
        temp->data = elem;
        if ( *head == NULL ||  (*head)->data > temp->data) {
                temp->next = *head;
                *head = temp;
                 return ;
        }
        struct node *first = *head;

        while (first->next != NULL && first->next->data < temp->data)
        {
                first = first->next;

        }
        temp->next = first->next;
        first->next = temp;

}
