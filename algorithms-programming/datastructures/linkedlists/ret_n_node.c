/*

Given a Linked List and a number n, write a function that 
returns the value at the nth node from end of the Linked List

*/

void printNthFromLast(struct node *head, int n) 
{ 
	struct node *main_ptr = head; 
	struct node *ref_ptr = head; 
	int count = 0; 

	if(head != NULL) 
	{ 
		while( count < n ) 
		{ 
			if(ref_ptr == NULL) 
			{ 
				printf("%d is greater than the no. of " "nodes in list", n); 
				return; 
			} 
			ref_ptr = ref_ptr->next; 
			count++; 
		} /* End of while*/ 

		while(ref_ptr != NULL) 
		{ 
			main_ptr = main_ptr->next; 
			ref_ptr = ref_ptr->next; 
		} 
		printf("Node no. %d from last is %d ", n, main_ptr->data); 
	} 
} 
