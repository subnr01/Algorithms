/* 

Given a Linked List of integers, write a function to modify the linked list
such that all even numbers appear before all the odd numbers in the modified
linked list. Also, keep the order of even and odd numbers same.  Examples:

Input: 17->15->8->12->10->5->4->1->7->6->NULL 
Output:8->12->10->4->6->17->15->5->1->7->NULL 

Input: 8->12->10->5->4->1->6->NULL
Output: 8->12->10->4->6->5->1->NULL


*/


// If all numbers are even then do not change the list Input: 8->12->10->NULL Output: 8->12->10->NULL 
// If all numbers are odd then do not change the list Input: 1->3->5->7->NULL Output: 1->3->5->7->NULL

void seg ( struct node **head)
{

        struct node *odd = NULL;
        struct node *even = NULL;
        struct node *prev = NULL;

        struct node *temp= *head;

        while ( temp != NULL)
        {
                if ( temp->data % 2 != 0)
                {
                        prev = temp;
                        temp = temp->next;
                        prev->next = NULL;
                        if ( odd == NULL)
                        {
                                odd = prev;
                        }
                        else
                        {
                                prev->next = odd;
                                odd = prev;
                        }
                }
                else
                {
                        prev = temp;
                        temp = temp->next;
                        prev->next = NULL;
                        if (even == NULL)
                        {
                                even = prev;
                        }
                        else
                        {
                                prev->next = even;
                                even = prev;
                        }
                }
        }

        *head = even;
        while ( even->next != NULL)
                even = even->next;

        even->next = odd;
}
