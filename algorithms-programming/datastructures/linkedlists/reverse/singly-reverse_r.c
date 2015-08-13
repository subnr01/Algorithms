
/* 
Function to  reverse a linked list
recursively

*/


void reverse_r(struct node **head)
{
	if (!*head)
		return;

	struct node *first = *head;
	struct node *last = NULL;
	last = first->next;
	if (!last)
		return;
	reverse_r(&last);

	last->next=first;
	first->next = NULL;

	*head = last;
}