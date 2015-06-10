
/*

Given a binary tree,
Create a linked list at each depth

*/


1. Declare an array of linked lists
2. Declare a dummy list and add root to it
3. Add the above dummy list to the array of linked lists.
4. Run a loop until true
5. Declare a dummy list. 
6. Run a inner loop until the size of the the number of nodes in the previous level.
7. Add the children of the nodes in the previous level into this dummy list.
8. Add this dummy list to the array of linked lists. This dummy list will now serve as input to
   the next iteration of the inner for loop.



 vector<list> getlinkedlists ( struct node *root )
 {
 	vector<list> newList = new vector<list>();
 	int level = 0;
 	list dummy = new list;

 	dummy.add(root);
 	newList.add(level, dummy);

 	while (true)
 	{
 		list dummy = new list;
 		for ( i to newList.get(level).size())
 		{
 			struct node *temp  = newList.get(level).get(i);
 			if ( temp->left) {
 				dummy.add(temp->left);
 			}
 			if (temp->right)
 			{
 				dummy.add(temp->right);
 			}


 		}

 		if (dummy.size)
 		{
 			newList.add(level + 1,dummy);
 		}
 		else
 		{
 			break;  //Notice break here
 		}
 		level++; //why not increment level after the loop????
 	}

 	return newList;

 }

