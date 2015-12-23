/*

Detect and remove loop
in linked list



Method 2 (Efficient Solution)
This method is also dependent on Floyd’s Cycle detection algorithm.
1) Detect Loop using Floyd’s Cycle detection algo and get the pointer to a loop node.
2) Count the number of nodes in loop. Let the count be k.
3) Fix one pointer to the head and another to kth node from head.
4) Move both pointers at the same pace, they will meet at loop starting node.
5) Get pointer to the last node of loop and make next of it as NULL.


*/

/*
Method 3 Effecient
*/

void detectAndRemoveLoop(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;
 
    // Search for loop using slow and fast pointers
    while (fast && fast->next)
    {
        if (slow == fast)
            break;
        slow = slow->next;
        fast = fast->next->next;
    }
 
    /* If loop exists */
    if (slow == fast)
    {
        slow = head;
        while (slow != fast->next)
        {
            slow = slow->next;
            fast = fast->next;
        }
 
        /* since fast->next is the looping point */
        fast->next = NULL; /* remove loop */
    }
}

    
    
    
    
    
    
 
   
