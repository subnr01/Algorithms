/*

Given a linked list, write a function to reverse every k nodes
 (where k is an input to the function).

Example:
Inputs:  1->2->3->4->5->6->7->8->NULL and k = 3 
Output:  3->2->1->6->5->4->8->7->NULL. 

Inputs:   1->2->3->4->5->6->7->80->NULL and k = 5
Output:  5->4->3->2->1->8->7->6->NULL. 

*/


struct node* reverse_k_nodes( struct node *head, int k)
{
	if ( !head || !k)
		return;

	int n = k;
	struct node *current = head;
	struct node *prev = NULL;
	struct node *next;

	while (current != NULL && n > 0)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
		n--;
	}

	if ( current != NULL)
	{	
		head->next = reverse_k_nodes(current,k)
	}

	return prev;
}
