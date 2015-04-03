
/*

Given a singly linked list, write a function to swap elements pairwise. 

For example, if the linked list is 1->2->3->4->5 then the 
function should change it to 2->1->4->3->5, and if the linked list
is 1->2->3->4->5->6 then the function should change it to 2->1->4->3->6->5.

 */


Iterative Method


void pairwise_swap(struct node *head)
{
	if ( !head)
		return;

	struct node *current = head;
	struct node *next = current->next; 
	
	while (current != NULL && next != NULL)
	{
		swap (&current->data,&next->data);
		current = next->next;

		if (current)
			next = current->next;
	}

}


void pairwise_swap_r(struct node *head)
{
	if (!head || !head->next)
		return;

	swap (&head->data,&head->next->data);
	pairwise_swap_r(head->next->next);
}