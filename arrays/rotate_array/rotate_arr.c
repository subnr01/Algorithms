/*

Write a function rotate(ar[], d, n) that rotates arr[] of size n by d elements


/*Function to left rotate arr[] of size n by d*/ 
void leftRotate(int arr[], int d, int n) 
{ 
int i; 
for (i = 0; i &lt; d; i++) 
	leftRotatebyOne(arr, n); 
} 


void leftRotatebyOne(int arr[], int n) 
{ 
int i, temp; 
temp = arr[0]; 

for (i = 0; i < n-1; i++) 
	arr[i] = arr[i+1]; 

arr[i] = temp; 
} 
