#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <unordered_map>


int orderOperations(const std::string &op){
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

bool isOperator(const std::string &token){
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double calculations(double a, double b, const std::string &op){
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/"){
        if (b == 0) throw std::runtime_error("Division by zero");
        return a/b;
    }
    throw std::runtime_error("Invalid operator");
}

std::vector<std::string> inFlixToPostflix(const std::vector<std::string> &tokens){
    std::vector<std::string> postfix;
    std::stack<std::string> operators;
    for (size_t i = 0; i <tokens.size(); ++i){
        const auto &token = tokens[i];

        if (std::isdigit(token[0])){
            postfix.push_back(token);
        }else if (token == "("){
            operators.push(token);
        }else if (token == ")"){
            while (!operators.empty() && operators.top() != "("){
                postfix.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty() && operators.top() == "("){
                operators.pop();
            }
        } else if (isOperator(token)){
            if (token == "-" && (i == 0 ||tokens[i-1] == "(")){
                postfix.push_back("0");
            }
            while (!operators.empty() && orderOperations(operators.top()) >= orderOperations(token)){
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }
    while (!operators.empty()){
        postfix.push_back(operators.top());
        operators.pop();
    }
    return postfix;
}

double evaluatePostfix(const std::vector<std::string> &postfix){
    std::stack<double> values;
    for (const auto &token : postfix){
        if (std::isdigit(token[0])){
            values.push(std::stod(token));
        } else if (isOperator(token)) {
            if (values.size() < 2) throw std::runtime_error("Invalid expression");
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(calculations(a, b, token));
        }
    }
    if (values.size() != 1) throw std::runtime_error("Invalid expression");
    return values.top();
}

double evaluateExpression(const std::vector<std::string> &input){
    auto postfix = inFlixToPostflix(input);
    return evaluatePostfix(postfix);
}

int main(){
    std::vector<std::string> input = {"(","-","(","1","-","2",")",")"};
    try{
        double result = evaluateExpression(input);
        std::cout<<"Result: " <<result <<std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr <<"Error: " <<e.what() <<std::endl;
    }
    return 0;
}

