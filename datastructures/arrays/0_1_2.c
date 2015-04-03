
/*

Given an array A[] consisting 0s, 1s and 2s, write a function that sorts A[]. 
The functions should put all 0s first, then all 1s and all 2s in last.
*/



void sort012(int a[], int arr_size) 
{ 
int lo = 0; 
int hi = arr_size - 1; 
int mid = 0; 
while(mid <= hi) 
{ 
switch(a[mid]) 
{ 
case 0: swap(&a[lo++], &a[mid++]); break; 
case 1: mid++; break; 
case 2: swap(&a[mid], &a[hi--]); break; 
} }}

