/*
Find minimum in rotated array
1. Without duplicates.
2. Without duplicates.

Refer leet code
*/


/*
With duplicates
*/
 int findMin(vector<int> &num) {
        int start=0,end=num.size()-1;
        
        while (start<end) {
            if (num[start]<num[end])
                return num[start];
            
            int mid = (start+end)/2;
            
            if (num[mid]>=num[start]) {
                start = mid+1;
            } else {
                end = mid;
            }
        }
        
        return num[start];
}


/* 
With duplicates
*/


    
    
    
