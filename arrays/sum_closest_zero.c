/*

An Array of integers is given, both +ve and -ve. 
You need to find the two elements such that their 
sum is closest to zero.



*/



Solution:
Steps:
1.	Sort the array.
2.	Use two indexes left and right to traverse from left and right.
3.	Left = 0 and right = n-1. Add left and right.
4.	If sum is +ve, then left++
5.	If sum is –ve then right --;
6.	Repeat until left>right.  


7.	while(l < r)
8.	  {
9.	    sum = arr[l] + arr[r];
10.	 
11.	    /*If abs(sum) is less then update the result items*/
12.	    if(abs(sum) < abs(min_sum))
13.	    {
14.	      min_sum = sum;
15.	      min_l = l;
16.	      min_r = r;
17.	    }
18.	    if(sum < 0)
19.	      l++;
20.	    else
21.	      r--;
22.	  }
23.	 
