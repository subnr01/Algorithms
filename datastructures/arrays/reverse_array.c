Write a program to reverse an array
Solution 1:
Iterative
while(start < end) 
{ 
temp = arr[start]; 
arr[start] = arr[end]; 
arr[end] = temp; 
start++; 
end--; 
} 

Solution 2
Recursive
void revereseArray(int arr[], int start, int end) 
{ 
int temp; 
if(start >= end) 
return; 
temp = arr[start]; 
arr[start] = arr[end]; 
arr[end] = temp; 
revereseArray(arr, start+1, end-1); 
} 
