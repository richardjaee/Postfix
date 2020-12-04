#include <string>
#include <stack>
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;


int precedence(char ch);
const int invalid = 1;
const int valid = 0;

int evaluate(const string& infix, string& postfix, bool& result){
  // Evaluates a boolean expression
           //   If infix is a syntactically valid infix boolean expression,
           //   then set postfix to the postfix form of that expression, set
           //   result to the value of the expression, and return zero.  If
           //   infix is not a syntactically valid expression, return 1; in
           //   that case, postfix may or may not be changed, but result must
           //   be unchanged.

      

    postfix = ""; //initialize postfix to empty
    stack<char> operatorStack; //Initialize the operator stack to empty
    char prevChar = '^'; //initialize previous character to be an operator
    

    for (int i = 0; i < infix.size(); i++) //For each character ch in the infix string
    {
        char ch = infix[i];
        
        switch(ch)
        {
            
                
            case 'T': //case operand
            case 'F':
                if (prevChar == 'T' || prevChar == 'F' || prevChar == ')'){
                    return invalid;
                }
                postfix += ch; //append ch to end of postfix
                break;
            
            case '(':
            
                if (prevChar == 'T' || prevChar == 'F' || prevChar == ')'){
                    return invalid;
                }
                operatorStack.push(ch); //push onto operator stack
                break;
            
                
            case ')':
                if (prevChar != 'T' && prevChar != 'F' && prevChar != ')'){
                    return invalid;
                }
                while(operatorStack.top() != '(') //pop stack until matching (
            {
                postfix += operatorStack.top(); //append stack top into postfix
                operatorStack.pop(); //pop the stack
                
            }
                operatorStack.pop();
            break;

                
          case '^': //case operator
          case '&':
          case '!':
                if (ch != '!' && prevChar != 'T' && prevChar != 'F' && prevChar != ')'){
                    return invalid;
                }
                while (! operatorStack.empty() && operatorStack.top() != '(' && precedence(ch) <=  precedence(operatorStack.top()) )
                    //While the stack is not empty and the stack top is not '('and precedence of ch <= precedence of stack top
            {
                postfix += operatorStack.top(); //append the stack top to postfix
                operatorStack.pop(); //pop the stack
                
            }
                operatorStack.push(ch); //push ch onto the stack //here
                break;
                
            case ' ':
                continue;
                
            default:
                return invalid;
        }
        prevChar = ch;
       
        }
    
    
    if (prevChar != 'T' && prevChar !='F' && prevChar != ')'){
        return invalid;
    }
    while (! operatorStack.empty()){ //while the stack is not empty //here maybe?
        
        char chc = operatorStack.top();
                 
        operatorStack.pop(); //pop the stack
        if (chc == '('){
         return invalid;
    }
       postfix += chc;
    
    }

     
//evaluation of postfix expression
    stack<bool> operandStack; //operand stack is now empty
    
    for (int k = 0; k < postfix.size(); k++)
    {
        char ch = postfix[k];
        
        if (ch == 'T') //if ch is an operand
            operandStack.push(true);
        else if (ch == 'F') //if ch is an operand
            operandStack.push(false);
        
        else //ch is a binary operator
        {
            bool operand2 = operandStack.top(); //set operand 2 to the top of the stack
            operandStack.pop();
            if (ch == '!'){
                operandStack.push(!operand2);
            }
            else {
            bool operand1 = operandStack.top(); //set operand 1 to the top of the stack
            operandStack.pop();
                if (ch == '&'){
                operandStack.push(operand1 && operand2);
                }
                else if (ch == '^'){
                operandStack.push(operand1 || operand2);
                }
                else
                return invalid;
                        
            }
       }
  
    
    
    
}
    result = operandStack.top();
    return valid;
}

int precedence(char ch)
{ // ! has higher precedence than &, which has higher precedence than ^, operators of equal precedence associate left to right
    int prec = 0;
        if (ch == '!'){
    prec = 4;
        }
        else if (ch == '&'){
    prec = 3;
        }
        else if (ch == '^'){
    prec = 2;
        }
        else if (ch == '('){
    prec = 5;
        }
    return prec;
}


int main()
{
string pf;
bool answer;
assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
assert(evaluate("T^", pf, answer) == 1);
assert(evaluate("F F", pf, answer) == 1);
assert(evaluate("TF", pf, answer) == 1);
assert(evaluate("()", pf, answer) == 1);
assert(evaluate("()T", pf, answer) == 1);
assert(evaluate("T(F^T)", pf, answer) == 1);
assert(evaluate("T(&T)", pf, answer) == 1);
assert(evaluate("(T&(F^F)", pf, answer) == 1);
assert(evaluate("T|F", pf, answer) == 1);
assert(evaluate("", pf, answer) == 1);
assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
cout << "Passed all tests" << endl;
}

