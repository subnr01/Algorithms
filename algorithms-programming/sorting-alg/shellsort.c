/*

Shell sort

Siedwick:

Insertion sort is slow for large un- ordered arrays because the only exchanges 
it does involve adjacent entries, so items can move through the array only one 
place at a time. For example, if the item with the 
smallest key happens to be at the end of the array, 
n-1 exchanges are needed to get that one item where it belongs.

Shellsort is a simple extension of insertion sort that gains speed by 
allowing exchanges of array entries that are far apart, to produce partially
sorted arrays that can be efficiently sorted, eventually by insertion sort.

The idea is to rearrange the array to give it the property that taking every
hth entry (starting anywhere) yields a sorted subsequence. Such an array
is said to be h-sorted. 

Put another way, an h-sorted array is h inde- pendent sorted subsequences, 
interleaved together. By h-sorting for some large val- ues of h, we can move items 
in the array long distances and thus make it easier to h-sort for smaller values of h. 
Using such a procedure for any sequence of values of h that ends in 1 will produce a 
sorted ar- ray: that is shellsort. 

We use values starting at the largest increment less than N/3 and decreasing to 1. 
We refer to such a sequence as an increment sequence

One way to implement shellsort would be, for each h, to use insertion sort indepen-
dently on each of the h subsequences. Because the subsequences are independent, 
we can use an even simpler approach: when h-sorting the array, 
we insert each item among the previous items in its h-subsequence by 
exchanging it with those that have larger keys (moving them each one position to 
the right in the subsequence). We accomplish this task by using the insertion-sort 
code, but modified to decrement by h instead of 1 when moving through the array. 
This observation reduces the shellsort implementa- tion to an insertion-sort-like 
pass through the array for each increment.

Shellsort gains efficiency by making a tradeoff between size and 
partial order in the subsequences. At the beginning, the subsequences are 
short; later in the sort, the subse- quences are partially sorted. In both cases, 
insertion sort is the method of choice. The extent to which the subsequences are
partially sorted is a variable factor that depends strongly on the increment 
sequence. Understanding shellsort’s performance is a chal- lenge.

*/


     void sort(int  *a)
     {  // Sort a[] into increasing order.
        int N = a.length;
        int h = 1;
        while (h < N/3) h = 3*h + 1; // 1, 4, 13, 40, 121, 364, 1093, ...
        while (h >= 1)
        {  // h-sort the array.
           for (int i = h; i < N; i++)
           {  // Insert a[i] among a[i-h], a[i-2*h], a[i-3*h]... .
              for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
                 exch(a, j, j-h);
		   }
		   h = h/3; 
		}
     }


/*

How do we decide what increment sequence to use? In general, this question 
is a difficult one to answer. The performance of the algorithm depends not just on 
the num- ber of increments, but also on arithmetical interactions among the increments such as
the size of their common divi- sors and other properties. Many different increment 
sequences have been studied in the lit- erature, but no provably best sequence has been found

Shellsort is useful even for large arrays, particularly by contrast with selection
 sort and insertion sort. It also performs well on arrays that are in arbitrary 
 order (not necessarily ran- dom). 

Shellsort is much faster than insertion sort and selection sort, and its speed 
advantage increases with the array size. 

The running time is not necessarily quadratic. 
The above algorithm runs with N ^ (3/2).

*/