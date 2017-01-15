/*


Given two lists, merge their nodes together to make one list, taking nodes alternately
between the two lists. So ShuffleMerge() with {1, 2, 3} and {7, 13, 1} should yield {1, 7,
2, 13, 3, 1}. If either list runs out, the all the nodes should be taken from the other list.


*/


struct node *ShuffleMerge(struct node *head1, struct node *head2)
{
	struct node temp;
	struct node *start = &temp;


	while (head1 != NULL && head2 != NULL)
	{
		start->next = head1;
		start = head1;
		head1 = head1->next;
		start->next = head2;
		
		/* this step is important */
		start = head2;
		
		head2 = head2->next;
	}	
	if(head1)
	{
		start->next = head1;
	}
	if(head2)
	{
		start->next = head2;
	}

	start->next = NULL;
	return temp.next;
}



struct node *ShuffleMerge_r(struct node *head1, struct node *head2)
{
	if (!head1)
		return head2;
	else if (!head2)
		return head1;
	else
	{
		/* what happens when null is returned */
		struct node *recur = ShuffleMerge_r(head1->next, head2->next);
		struct node *result = head1;
		head1->next = head2;
		head2->next = recur;
		return result;
	}
	return NULL;
}			

	}



}
