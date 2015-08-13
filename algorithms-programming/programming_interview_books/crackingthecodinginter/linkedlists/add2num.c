

/*

Add two numbers represented by
a linked list

*/


struct node *add( struct node *head1, struct node *head2, int carry)
{
	struct node *result  = getnode(carry);

	int temp = 0;

	if (head1)
	{
		temp += head1->data;
	}

	if (head2)
	{
		temp += head2->data;
	}

	result->data = temp%10;


	struct node *p = add( head1 ? head1->next : NULL, head2 ? head2->next : NULL, temp > 10 );

	result->next = temp;
	return result;x

}
