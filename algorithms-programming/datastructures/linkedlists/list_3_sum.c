
/*

Given three linked lists, say a, b and c, find one node from each list such that
the sum of the values of the nodes is equal to a given number.  For example, if
the three linked lists are 12->6->29, 23->5->8 and 90->20->59, and the given
number is 101, the output should be tripel “6 5 90″.

*/


/*

Sorting can be used to reduce the time complexity to O(n*n). Following are the detailed steps.
1) Sort list b in ascending order, and list c in descending order.
2) After the b and c are sorted, one by one pick an element from list a and 
   find the pair by traversing both b and c. 

*/


bool isSumSorted(struct node *headA, struct node *headB, 
                 struct node *headC, int givenNumber)
{
    struct node *a = headA;
 
    // Traverse through all nodes of a
    while (a != NULL)
    {
        struct node *b = headB;
        struct node *c = headC;
 
        // For every node of list a, prick two nodes from lists b abd c
        while (b != NULL && c != NULL)
        {
            // If this a triplet with given sum, print it and return true
            int sum = a->data + b->data + c->data;
            if (sum == givenNumber)
            {
               printf ("Triplet Found: %d %d %d ", a->data, b->data, c->data);
               return true;
            }
 
            // If sum of this triplet is smaller, look for greater values in b
            else if (sum < givenNumber)
                b = b->next;
            else // If sum is greater, look for smaller values in c
                c = c->next;
        }
        a = a->next;  // Move ahead in list a
    }
 
    printf ("No such triplet");
    return false;
}


