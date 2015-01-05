/*

Stack that Support Push, Pop, and GetMin in Constant Time

*/


/*
Solution

Initially I thought of using an extra min-heap to store the elements. Although
this enables us to retrieve the minimum element in O(1), push and pop operations
both operates in O(lg N), where N is the total number of elements in the stack.
Definitely not a desirable method.



How about recording the current minimum in the stack? This works until you pop
current minimum off the stack, where you would have to update your next minimum,
which takes O(N) time to examine all elements.

The solution is surprisingly simple and elegant — Use an extra stack to maintain
the minimums. What does this mean?



To retrieve the current minimum, just return the top element from minimum stack.
Each time you perform a push operation, check if the pushed element is a new
minimum. If it is, push it to the minimum stack too. When you perform a pop
operation, check if the popped element is the same as the current minimum. If it
is, pop it off the minimum stack too.


All of the above operates in O(1) constant time.

A Gotcha:
There is one small gotcha I purposely left in the above solution. 
Could you figure it out without looking at the code below first?

*/

struct StackGetMin {
  void push(int x) {
    elements.push(x);
    if (minStack.empty() || x <= minStack.top())
      minStack.push(x);
  }
  bool pop() {
    if (elements.empty()) return false;
    if (elements.top() == minStack.top())
      minStack.pop();
    elements.pop();
    return true;
  }
  bool getMin(int &min) {
    if (minStack.empty()) {
      return false;
    } else {
      min = minStack.top();
      return true;
    }
  }
  stack<int> elements;
  stack<int> minStack;
};


/*
Gotcha
If the value being pushed is equal to the current minimum, you push that value to the minimum stack as well. 
Is this the gotcha you were referring to?

*/





