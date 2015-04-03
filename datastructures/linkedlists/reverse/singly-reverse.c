/*

Function to reverse a linked list
iteratively

*/


void reverse (struct node **head)
{
	if (!*head)
		return;

	struct node *curr = *head;
	struct node *prev=NULL;
	struct node *next;

	while (cur != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	*head = prev;

}


