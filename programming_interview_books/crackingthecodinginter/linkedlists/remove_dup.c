/*
Remove duplicates from a unsorted linked list
*/


/*
Using hash table 
*/


void removedup(struct node *head)
{
	bool *hash[256];

	struct node *temp, *prev;
	temp = head;
	

	while (temp != NULL)
	{
		if (hash[temp->data])
			remove(prev,temp);

		hash[temp->data] = 1;
		prev = temp;
		temp = temp->next;
	}

}


/*
Without any temporary buffers

Move current whenever there is a match.
Move runner from start to end
everytime you want to find a 
duplicate.
*/

void removedup (struct node *head)
{
	if (!head) {
		return;
	}
	struct node *prev = head;
	struct node *current = head->next;

	while ( current != NULL)
	{
		struct node *p = head;
		while ( p != current)
		{
			if ( p->data == current->data)
			{
				struct node *temp = current->next;
				prev->next = temp;
				free(current);
				current = temp;
				break;
			}

			if ( p == current)
			{
				prev = current;
				current = current->next;
			}
			
		}
	}


	

}
