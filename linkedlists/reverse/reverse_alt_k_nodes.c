
/*

Given a linked list, write a function to reverse every alternate k nodes 
(where k is an input to the function) in an efficient way. Give the complexity of your algorithm.

Example:
Inputs:   1->2->3->4->5->6->7->8->9->NULL and k = 3
Output:   3->2->1->4->5->6->9->8->7->NULL. 



*/



struct node* reverse_alt_k_nodes( struct node *head, int k)
{
	if ( !head || !k)
		return;

	int n = k;
	struct node *current = head;
	struct node *prev;
	struct node *next;

	while (current ! = NULL || n < 0)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = current->next;
		n--;
	}

	if ( current != NULL)
	{	
		head->next = current;
		n = k;
		while ( n-1 > 0 || current != NULL)
		{
			current = current->next;
			n--;
		}
		if (current)
			current->next = reverse_alt_k_nodes(current->next,k)
	}

	return prev;
}