


/* 
Delete a node in a doubly linked list

*/


void delete(struct node **head, int key)
{
	if(!*head)
		return;

	struct node *curr = *head;

	if (*head->data == key)
	{
		*head = *head->next;
		free(curr);
		*head->prev = NULL;
	}

	
	while (curr != NULL)
	{
		if (key == curr->data)
		{
			(curr->prev)->next = curr->next;
			if (curr->next)
				(curr->next)->prev = curr->prev;
			free(curr);
			return;
		}
	}


}