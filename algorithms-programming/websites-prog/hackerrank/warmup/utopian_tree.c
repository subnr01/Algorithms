/*
The Utopian Tree goes through 2 cycles of growth every year. The first growth cycle occurs 
during the spring, when it doubles in height. The second growth cycle occurs during 
the summer, when its height increases by 1 meter.

Now, a new Utopian Tree sapling is planted at the onset of spring. Its height is 1 meter. 
Can you find the height of the tree after N growth cycles?

*/

int main()
{
	printf("The number of cycles");
	printf("%d\n", n);
	int height = 1;

	for (i = 1; i <= n; i++)
	{
		if ( n %2 )
		{
			height++;
		} else {
			height+=2*height;
		} 

	}
}