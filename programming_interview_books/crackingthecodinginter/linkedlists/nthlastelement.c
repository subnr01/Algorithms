/*

Find nth to last element
in a linked list 
*/

1--> 2 --> 3 --> 4 --> 5 --> 6

void findnthlastelement( struct node *head, int n)
{
	if (!head || n < 1)
		return;


	struct node *p = head;
	struct node *q = head;

	while ( n != 0 )
	{
		p = p->next;
		if (!p)
		{
			return;
		}
		n--;
	}

	/* Watch the p->next */
	while ( p->next != NULL)
	{
		p = p->next;
		q = q->next;
	}

	printf("\n %d\n", q->data);

}