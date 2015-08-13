/*

While there are input tokens left
    read the next token
        if the token is an operand
            push it into the stack
        else
            pop the top two elements in the stack
            Perform the airthmetic operation
            push the result into the stack
        fi

The value left in the stack is the final result


*/


#include <stack>
#include <ctype.h>
 
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        // The stack to store operators (int values) only
        std::stack<int> res;
        int x,y;
        // Iterate the vector from left to right
        for(std::vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++)
        {
            // If operator, pop and evaluate
            if ( (*it).length() == 1 && !isdigit((*it)[0]) ) {
                y = res.top();
                res.pop();
                x = res.top();
                res.pop();
                if (*it == "+") x += y;
                else if (*it == "-") x -= y;
                else if (*it == "*") x *= y;
                else if (*it == "/") x /= y;
                res.push(x);
            }
            // If operand, push it into the stack
            else res.push( atoi((*it).c_str()) );
        }
        // The only value left in the stack is the final result
        return res.top();
    }
};
