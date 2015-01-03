

/* 

Merge two sorted linked lists
*/

struct node* mergeSorted_rec(struct node *head1, struct node *head2)
{

        struct node *result = NULL;
        struct node *temp = NULL;

        if ( head1 == NULL ) {
                result = head2;
                return result;
        }
        else if (head2 == NULL) {
                result = head1;
                return result;
        }

        if ( head1->data <= head2->data) {
                result = head1;
                result->next =  mergeSorted_rec(head1->next, head2);
        }
        else
        {
                result = head2;
                result->next =  mergeSorted_rec(head1, head2->next);
        }
                return result;
}

