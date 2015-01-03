/*

Check whether two linked lists are identical
*/


bool isIdentical (struct node *head1, struct node *head2)
{
	if (head1 == NULL && head2 == NULL)
		return true;

	if (head1 == NULL || head2 == NULL)
		return false;

	
	return ((head1->data == head2->data) &&  isIdentical(head1->next,head2->next);

}


