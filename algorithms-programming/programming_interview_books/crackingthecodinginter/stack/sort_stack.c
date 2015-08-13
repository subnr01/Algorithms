/* 
sort a stack to ascending order 
*/

stack sort ( stack s1)
{
	stack r1 = new stack;

	while ( s1.empty() != false)
	{
		int elem = s1.top;
		while ( r1.empty() != false && r1.top > elem) {
			s1.push(r1.pop());	
		}
		r1.push(elem);
	}
	return r1;
}