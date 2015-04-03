/*

You are given an array of 0s and 1s in random order. 
Segregate 0s on left side and 1s on right side of the array. 
Traverse array only once. 

*/


1.	Maintain two indexes left and right.
2.	Increment left if it is 0 and decrement right if it is 1.
3.	Swap left and right when left = 1 and right =0 until left< right.

while(left < right) 
{ 
	/* Increment left index while we see 0 at left */ 
	while(arr[left] == 0 && left < right) 
		left++; 

	/* Decrement right index while we see 1 at right */ 
	while(arr[right] == 1 && left < right) 
		right–; 


	/* If left is smaller than right then there is a 1 at left 
		and a 0 at right. Exchange arr[left] and arr[right]*/ 
	if(left < right)  {
		arr[left] = 0; 
		arr[right] = 1; 
		left++; 
		right–; 
	}
} 
