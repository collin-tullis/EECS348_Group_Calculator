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
    bool isOperator(string s){
        if (operators.find(s) != -1){
            return true;
        } else {
            return false;
        }
    }
    bool isNumber(string s){
        for (char c : s){
            if (digits.find(s) == -1){
                return false;
            } return true;
        }
    }
    bool validParentheses(vector<string> s){
        int count = 0;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == "(") {
                count++;
            }
            else if(s[i] == ")"){
                count--;
            }
            if (count < 0) {
                // more closing parenthises than open ones
                return false;
                break;
            }
	    }
    
        // more open perentheses than close
        if (count != 0) {
            return false;
        }

	    return true;
    }
    public:           
        ErrorHandler(vector<string> input ) {   
            try
            {
                for (int i = 0; i < input.size(); i++) {
                    if (isOperator(input[i])) {
                        // we are at an operator
                        if(i>0 && i<input.size()-1){
                            if (isOperator(input[i])){ // if the input after the input we are at is an operator than we have an error
                                throw invalid_argument("Invalid Operator Placement");
                            }
                        } else{
                            throw invalid_argument("Invalid Operator Placement"); // starting or ending with an operatior
                        }
                        // divide by zero error
                        if (input[i]=="/" && input[i+1]=="0"){
                            throw domain_error("Division by Zero");
                        }
                        // modulo by zero error
                        if (input[i]=="%" && input[i+1]=="0"){
                            throw domain_error("Modulo by Zero");
                        }


                    } else {
                        if (!isNumber(input[i]) && (input[i] != "(" || input[i] != ")")){
                            throw invalid_argument("Invalid Characters"); // if what the error handler recivies is not a valid number or operator there is an error

                        }
                    }
                }
                if (!validParentheses(input)){
                    throw invalid_argument("Paratheses error");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
};