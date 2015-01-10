/*

Given an image, how will you turn it by 90 degrees?

An image can be treated as 2D matrix which can be stored in a buffer. 
We are provided with matrix dimensions and it’s base address. How can we turn it?

An image can be treated as 2D matrix which can be stored in a buffer. 
We are provided with matrix dimensions and it’s base address. How can we turn it?

*/



int rotateby90(int dest_buffer[][], int source_buffer[][], int m, int n)
for(r = 0; r < m; r++)
{
   for(c = 0; c < n; c++)
   {
      // Hint: Map each source element indices into
      // indices of destination matrix element.
       dest_buffer [ c ] [ m - r - 1 ] = source_buffer [ r ] [ c ];
   }
}