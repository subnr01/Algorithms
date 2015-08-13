
void insertionSort(int ar_size, int *  ar) {
    int i, j , temp;
    
    for(i = 1; i < (ar_size-1); i ++)
    {
        j = i;
        temp = ar[i];
       

        for ( j = i ; j > 0 && ar[j-1] > temp; j--)
        {
        	/* 
        	   we found that temp is lesser that the 
        	   previous element so both a[j] and 
        	   a[j=1] are same now.
			*/
        	ar[j] = ar [j-1];
        } 
        ar[j] = temp;
     }  
        printar(ar_size, ar);
    }
}

/*
7 6 5 3
6 7 5 3

6 7 5 3
6 7 7 3
6 6 7 3
5 6 7 3

and ...

*/