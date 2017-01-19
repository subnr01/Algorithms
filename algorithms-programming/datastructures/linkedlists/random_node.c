/*

You are given a Double Link List with one pointer of each node pointing to the
next node just like in a single linkedlist. The second pointer however CAN point
to any node in the list and not just the previous node. Now write a program in
O(n) time to duplicate this list. That is, write a program which will create a
copy of this list.

http://www.geeksforgeeks.org/a-linked-list-with-next-and-arbit-pointer/
http://www.geeksforgeeks.org/clone-linked-list-next-arbit-pointer-set-2/
*/


/* Method 2 (Uses Constant Extra Space) Thanks to Saravanan Mani for providing
this solution. This solution works using constant space. 

1) Create the copy of node 1 and insert it between node 1 & node 2 
   in original Linked List, create the copy of 2 and insert it between 
   2 & 3.. Continue in this fashion, add the copy of N afte the Nth node 

2) Now copy the arbitrary link in this fashion 

original->next->arbitrary = original->arbitrary->next;  

This works because original->next is nothing but copy of original and
Original->arbitrary->next is nothing but copy of arbitrary. 

3) Now restore the original and copy linked lists in this fashion in a single loop.
  
   original->next = original->next->next;      
   copy->next = copy->next->next;

4) Make sure that last element of original->next is NULL.

Time Complexity: O(n) Auxiliary Space: O(1)

*/


Node* cloneList(Node *origList)
{
    Node *pClonedList = NULL;
    Node *temp = origList;
    /*Lets make a copy of each node adjecent to it
      Now 1->2->NULL becomes 1->1->2->2->NULL
    */
    while(temp != NULL)
    {
        Node *newNode = new Node(temp->data);
        Node *temp1 = temp->pNext;
        temp->pNext = newNode;
        newNode->pNext = temp1;
        temp = temp->pNext->pNext;
    }

    /*Now make the random assignment like:
      node->pNext->pRandom = node->pRandom->pNext
      which exactly does the cloning of random linking
    */
    temp = origList;
    while(temp != NULL)
    {
        temp->pNext->pRandom = temp->pRandom->pNext;
        temp = temp->pNext->pNext;
    }
    /*Now Delink the original list from cloned list*/
    temp = origList;
    pClonedList = origList->pNext;
    while(temp != NULL)
    {
        Node *temp1 = temp->pNext;
        if(temp->pNext != NULL)
        	temp->pNext = temp->pNext->pNext;
        if(temp1->pNext != NULL)
			temp1->pNext = temp1->pNext->pNext;
        temp = temp->pNext;
    }
    return pClonedList;
}
