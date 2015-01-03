/*

Reverse a doubly linked list

*/

void reverse(struct node **head)
{
	if (*head == NULL)
		return;

	struct node *current = *head;
	struct node *prev = NULL;
	struct node *next;

	while (current != NULL)
	{
		current->prev = current->next;
		current->next = prev;
		prev = current;
		current = current->prev;
	}

	*head = prev;
}