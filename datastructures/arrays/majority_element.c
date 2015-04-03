/*

Majority Element: A majority element in an array A[] of size n is an element
that appears more than n/2 times (and hence there is at most one such element).
Write a function which takes an array and emits the majority element (if it
exists), otherwise prints NONE as follows:

       I/P : 3 3 4 2 4 4 2 4 4
       O/P : 4 

       I/P : 3 3 4 2 4 4 2 4
       O/P : NONE

*/


/*
METHOD 1 (Using Binary Search Tree)

Insert elements in BST one by one and if an element is already present then
increment the count of the node. At any stage, if count of a node becomes more
than n/2 then return. The method works well for the cases where n/2+1 
occurrences of the majority element is present in the starting of the array, for
example {1, 1, 1, 1, 1, 2, 3, 4}.


Time Complexity: If a binary search tree is used then time complexity will be
O(n^2). If a self-balancing-binary-search tree is used then O(nlogn) Auxiliary
Space: O(n)

*/



/*

METHOD 2 (Using Moore's voting algorithm)

*/


/* Function to print Majority Element */
void printMajority(int a[], int size)
{
  /* Find the candidate for Majority*/
  int cand = findCandidate(a, size);
  
  /* Print the candidate if it is Majority*/
  if(isMajority(a, size, cand))
    printf(" %d ", cand);
  else
    printf("NO Majority Element");
}
  
/* Function to find the candidate for Majority */
int findCandidate(int a[], int size)
{
    int maj_index = 0, count = 1;
    int i;
    for(i = 1; i < size; i++)
    {
        if(a[maj_index] == a[i])
            count++;
        else
            count--;
        if(count == 0)
        {
            maj_index = i;
            count = 1;
        }
    }
    return a[maj_index];
}
  
/* Function to check if the candidate occurs more than n/2 times */
bool isMajority(int a[], int size, int cand)
{
    int i, count = 0;
    for (i = 0; i < size; i++)
      if(a[i] == cand)
         count++;
    if (count > size/2)
       return 1;
    else
       return 0;
}
