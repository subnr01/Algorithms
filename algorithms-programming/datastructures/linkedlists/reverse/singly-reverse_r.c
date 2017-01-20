
/* 
Function to  reverse a linked list
recursively

*/


void reverse_r(struct node **head)
{
	if (!*head)
		return;

	struct node *first = *head;
	struct node *second = NULL;
	second = first->next;
	if (!second)
		return;
	reverse_r(&second);

	first->next->next=first;
	first->next = NULL;

	*head = second;
}
