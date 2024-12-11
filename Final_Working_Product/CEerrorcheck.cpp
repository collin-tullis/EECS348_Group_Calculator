#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

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
    //bool isNumber(string s)
    //{
        //cout << endl << stoi(s) << endl << isdigit(static_cast<char> (stoi(s))) << endl;
        //cout << "C thinks I'm a: " << typeid('i').name() <<endl;
        //return (typeid(9).name() == typeid(stoi(s)).name());

     bool isNumber(const string& str) {
    bool decimal = false;

    for (char c : str) {
        if (!isdigit(c)) {
            if (c == '.' && !decimal) {
                decimal= true; 
            } else {
                return false; 
            }
        }
    }

    return true; 
}  
   bool validParentheses(vector<string> s)
    {
        int count = 0;
        for (int i = 0; i < s.size(); i++) 
        {
            string token = s[i];
           // string leftOfToken = s[i-1];
            //string rightOfToken = s[i+1];

            if(i > 0 && i < s.size()-1)
            {
                string leftOfToken = s[i-1];
                string rightOfToken = s[i+1];
                if(token == "(" && (isNumber(leftOfToken))) 
                {
                    //cout << "Left token" << leftOfToken << "     Is number"  << isNumber(leftOfToken) << endl;
                    return false;
                }
                if(token == ")" && isNumber(rightOfToken))
                {
                    //cout << "right parn" << endl;
                    return false;
                }
            
                if(rightOfToken == ")" && token == "("){
                    throw invalid_argument("Invalid Parentheses");
                }
            }
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
        bool error(vector<string> input ) 
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
                            string leftOfToken = input[i-1];
                            string rightOfToken = input[i+1];

                            if (!isNumber(leftOfToken) || !isNumber(rightOfToken))
                            { 
                                // left = (
                                // token = - 
                                // Right = (
                                // 1+1))
                                if(token == "-")
                                {
                                    //invalid
                                    if(rightOfToken != "(" && !isNumber(rightOfToken))
                                    {
                                        throw invalid_argument("Invalid Operator Placement");
                                    }
                                }
                                /*
                                else if((rightOfToken != "(" || rightOfToken != ")"))
                                {
                                    cout << rightOfToken << endl;
                                    throw invalid_argument("Invalid Operator Placement2");
                                }*/
                            }
                            // divide by zero error
                            if (token =="/" && rightOfToken =="0")
                            {
                                throw domain_error("Division by Zero");
                            }
                            // modulo by zero error
                            if (token == "%" && rightOfToken =="0")
                            {
                                throw domain_error("Modulo by Zero");
                            }
                        }
                        
                        else if(token != "-" && token != "+")
                        {
                            cout << token << endl;
                            throw invalid_argument("Invalid Operator Placement");
                        }
                        /*
                        else
                        {
                            throw invalid_argument("Invalid Operator Placement2"); // starting or ending with an operatior
                        }*/

                    } 
                    else 
                    {
                        if (!isNumber(token) && (token != "(" && token != ")"))
                        {
                           // cout << token << endl;
                            throw invalid_argument("Invalid Characters"); // if what the error handler recivies is not a valid number or operator there is an error

                        }
                    }
                }
                //cout << "Validate" << endl;
                if (!validParentheses(input))
                {
                    throw invalid_argument("Paratheses error");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr<<e.what() << '\n';
                return false;
            }
            return true;

        }
};
/*
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
}*/