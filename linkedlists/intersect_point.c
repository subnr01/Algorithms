/*

Write a function to get the intersection point of two Linked Lists

Method 3(Using difference of node counts) 
1) Get count of the nodes in first list, let count be c1. 
2) Get count of the nodes in second list, let count be c2. 
3) Get the difference of counts d = abs(c1 – c2) 
4) Now traverse the bigger list from the first node till d nodes so that from here onwards both the lists have equal no of nodes. 
5) Then we can traverse both the lists in parallel till we come across a common node. (Note that getting a common node is done by comparing the address of the nodes)


*/


int getIntesectionNode(struct node* head1, struct node* head2) 
{ 
	int c1 = getCount(head1); 
	int c2 = getCount(head2); 
	int d; 
	if(c1 > c2) 
	{ 
		d = c1 - c2; 
		return _getIntesectionNode(d, head1, head2); 
	} 
	else 
	{ 
		d = c2 - c1; 
		return _getIntesectionNode(d, head2, head1); 
	} 
} 

int _getIntesectionNode(int d, struct node* head1, struct node* head2) 
{ 
	int i; 
	struct node* current1 = head1; 
	struct node* current2 = head2; 
	for(i = 0; i < d; i++) 
	{ 
		if(current1 == NULL) 
		{ 
			return -1; 
		} 
		current1 = current1->next; 
	} 
	while(current1 != NULL && current2 != NULL) 
	{ 
		if(current1 == current2) 
			return current1->data; 

		current1= current1->next; 
		current2= current2->next; 
} 
return -1; 
}
