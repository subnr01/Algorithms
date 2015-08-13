/*
Implement three stacks using
a single array
*/

/*
Static approach
for stack1 we use 0 to n/3
for stack2 we use n/3 to 2n/3
for stack3 we use 2n/3 to n
*/

#define STACKSIZE * 3

//global variables:
int stackindex[3] = {0,0,0};
int buf [STACKSIZE * 3];


void push(int stacknum, int elem, int *status)
{
	if (isFull(stacknum)) {
		*status = 1;
	}
	int index = 3*stacknum + stackindex[stacknum] + 1;
	stackindex[stacknum]++;
	buf[index] = elem;
	*status = 0;
	return;
}

int pop( int stacknum, int *status, int *elem)
{
	if ( isEmpty(stacknum) ) {
		*status = 1;
	}
	int index = 3*stacknum + stackindex[stacknum] ;
	stackindex[stacknum]--;
	*status = 0;
	*elem = buf[index];
}

int top( int stacknum)
{
	int index = 3*stacknum + stackindex[stacknum] ;
	return buf[index];
}

bool isEmpty( int stacknum)
{
	return (stackindex[stacknum] == 0);
}

bool isFull(int stacknum)
{
	return (stackindex[stacknum] == STACKSIZE);
}


/* 
Dynamic approach
Stacks can grow to any size
*/







