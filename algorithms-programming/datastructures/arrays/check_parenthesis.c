
Programming Interview Questions 14: Check Balanced Parentheses


Given a string of opening and closing parentheses, check whether it’s balanced.
We have 3 types of parentheses: round brackets: (), square brackets: [], and
curly brackets: {}. Assume that the string doesn’t contain any other character
than these, no spaces words or numbers. Just to remind, balanced parentheses
require every opening parenthesis to be closed in the reverse order opened. For
example ‘([])’ is balanced but ‘([)]‘ is not.


We scan the string from left to right, and every time we see an opening
parenthesis we push it to a stack, because we want the last opening parenthesis
to be closed first. Then, when we see a closing parenthesis we check whether the
last opened one is the corresponding closing match, by popping an element from
the stack. If it’s a valid match, then we proceed forward, if not return false.
Or if the stack is empty we also return false, because there’s no opening
parenthesis associated with this closing one. In the end, we also check whether
the stack is empty. If so, we return true, otherwise return false because there
were some opened parenthesis that were not closed.


bool ArePair(char opening,char closing)
{
    if(opening == '(' && closing == ')') return true;
    else if(opening == '{' && closing == '}') return true;
    else if(opening == '[' && closing == ']') return true;
    return false;
}
bool AreParanthesesBalanced(string exp)
{
    stack<char>  S;
    for(int i =0;i<exp.length();i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            S.push(exp[i]);
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if(S.empty() || !ArePair(S.top(),exp[i]))
                return false;
            else
                S.pop();
        }
    }
    return S.empty() ? true:false;
}
 


