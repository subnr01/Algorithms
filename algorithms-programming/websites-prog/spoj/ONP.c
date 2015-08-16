/*
 * ONP Transform the Expression
 *
 */


 /*
  
  Transform the algebraic expression with brackets into
  RPN form (Reverse Polish Notation).

Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*
at+bac++cd+^*

*/


/*
Algorithm:
1. Put the character in the output string.
2. Put the operator in the stack.
3. Continue doing this until end of input.
4. Pop the top of the stack and append it to the end of the string.
5. Perform the stack pop operation until the stack is empty

*/


int main ()
{
    int t;
    cin>>t;
    char str[1000];
    stack <char> s;
    while (t--) 
    {
        cin>>str;
        int len = strlen (str);

        for(int i=0;i<len;i++ ) 
        {
            if(isalpha(str[i]))
                cout << str[i];
            else if(str[i] == ')' ) 
            {
                cout << s.top ();
                s.pop ();
            }

            else if (str[i] != '(' )
                s.push (str[i]);
        }

        cout << endl;
    }

    return 0;
}
