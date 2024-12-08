#include <iostream>
#include <vector>
using namespace std;
 
/* things to handle.
division by zero
modulo by zero
non integer operands for modulo
unsupported operations/ things that arent a number or an operator we use.
invalaid parenthises
operaters that don't have a number before and after*/

/*this will likely require some editing as i don't fully understand what sort of input ill recive from the parser*/
/* also not entirly clear on output i have a try catch rn*/
/* i can't test stuff on my own because i failed to set c++ up on my computer */
class ErrorHandler {    
    string operators = "+-**/%";
    string digits = "0123456789";
    bool isOperator(string s)
    {
       
        if (operators.find(s) != -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool isNumber(string s)
    {
        for (char c : s)
        {
            if (digits.find(s) == -1)
            {
                return false;
            }
            return true;
        }
    }
    bool validParentheses(vector<string> s)
    {
        int count = 0;
 
        for (int i = 0; i < s.size(); i++)
        {
 
            if (s[i] == "(")
            {
                count++;
            }
            else if(s[i] == ")")
            {
                count--;
            }
            if (count < 0)
            {
                // more closing parenthises than open ones
                return false;
                break;
            }
        }
 
        // more open perentheses than close
        if (count != 0)
        {
            return false;
        }
 
        return true;
    }
    public:          
        ErrorHandler(vector<string> input )
        {  
            try
            {
                for (int i = 0; i < input.size(); i++)
                {
                    string token = input[i];
                    if (isOperator(token))
                    {
                        // we are at an operator
                        if(i>0 && i<input.size()-1)
                        {
                            string leftOfToken = input[i+1];
                            string rightOfToken = input[i+1];
                            if (!isNumber(leftOfToken) && !isNumber(rightOfToken))
                            {
                                // left = (
                                // token = -
                                // Right = 1
                                // (1+1))
                                if(rightOfToken != "(")
                                {
                                    cout << "Almost got there" << endl;
                                    throw invalid_argument("Invalid Operator Placement");
                                }
                            }
                        }
                        else
                        {
                            cout << "GOt there" << endl;
                            throw invalid_argument("Invalid Operator Placement"); // starting or ending with an operatior
                        }
                        // divide by zero error
                        if (token =="/" && input[i+1]=="0")
                        {
                            throw domain_error("Division by Zero");
                        }
                        // modulo by zero error
                        if (input[i]=="%" && input[i+1]=="0")
                        {
                            throw domain_error("Modulo by Zero");
                        }
 
 
                    }
                    else
                    {
                        if (!isNumber(token) && (token != "(" && token != ")"))
                        {
                            throw invalid_argument("Invalid Characters"); // if what the error handler recivies is not a valid number or operator there is an error
 
                        }
                    }
                }
                if (!validParentheses(input))
                {
                    throw invalid_argument("Paratheses error");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
 
        }
};

int main(){
    vector<string> vec;
    vec.push_back("(");
    vec.push_back("-");
    vec.push_back("1");
    vec.push_back("(");
    //cout << typeid(vec[0]).name() << endl;
    vec.push_back("1");
    vec.push_back("+");
    vec.push_back("1");
    vec.push_back(")");
    vec.push_back(")");
    //vec.push_back("");
    ErrorHandler myError = ErrorHandler(vec);

    return 1;
}