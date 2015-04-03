
/*

Write a removeDuplicates() function which takes a list sorted 
in non-decreasing order and deletes any duplicate nodes from 
the list. The list should only be traversed once.

For example if the linked list is 
11->11->11->21->43->43->60 then removeDuplicates() should convert the list to 11->21->43->60.


*/



struct node *removeDup( struct node *head)
{
	if (!head) 
		return;

	struct node *head = current;
	struct node *next;

	while (current->next != NULL)
	{
		if (current->data == current->next->data)
		{
			next = current->next;
			current = next->next;
			free(next);
			continue;
		}
		current=current->next;
	}


}
