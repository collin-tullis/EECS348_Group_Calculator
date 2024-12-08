#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <unordered_map>

class Evaluator {
public:
    // Main function to evaluate an expression from tokens
    double evaluateExpression(const std::vector<std::string>& input);

    // Function to evaluate a single input string directly
    double evaluateSingleExpression(const std::string& input);

private:
    // Helper functions
    int precedence(const std::string& op);
    bool isOperator(const std::string& token);
    double calculate(double a, double b, const std::string& op);
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
    double evaluatePostfix(const std::vector<std::string>& postfix);
};

// Define precedence for operators
int Evaluator::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "**") return 3;
    return 0;
}

// Check if a token is an operator
bool Evaluator::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "**" || token == "%";
}

// Perform calculations based on the operator
double Evaluator::calculate(double a, double b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if (op == "%") {
        if (b == 0) throw std::runtime_error("Modulo by zero");
        return static_cast<int> (a) % static_cast<int> (b);
    }
    if (op == "**") return std::pow(a, b);
    throw std::runtime_error("Invalid operator");
}

// Convert infix expression to postfix
std::vector<std::string> Evaluator::infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> postfix;
    std::stack<std::string> operators;

     for (size_t i = 0; i <tokens.size(); ++i){
        const auto &token = tokens[i];
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
            // Token is a number (handles negative numbers too)
            postfix.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                postfix.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop();
            }
        } else if (isOperator(token)) {
            if (token == "-" && (i == 0 ||tokens[i-1] == "(")){
                postfix.push_back("0");
            }
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
     }

    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop();
    }
    return postfix;
}

// Evaluate a postfix expression
double Evaluator::evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> values;

    for (const auto& token : postfix) {
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
            values.push(std::stod(token));
        } else if (isOperator(token)) {
            if (values.size() < 2) throw std::runtime_error("Invalid expression from 2");
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(calculate(a, b, token));
        }
    }

    if (values.size() != 1) throw std::runtime_error("Invalid expression from 1");
    return values.top();
}

// Evaluate an expression given as a vector of tokens
double Evaluator::evaluateExpression(const std::vector<std::string>& input) {
    auto postfix = infixToPostfix(input);
    return evaluatePostfix(postfix);
}

// Evaluate a single input string
double Evaluator::evaluateSingleExpression(const std::string& input) {
    std::vector<std::string> tokens;
    std::string number;

    for (char ch : input) {
        if (std::isspace(ch)) {
            continue;
        } else if (std::isdigit(ch) || ch == '.' || (ch == '-' && (tokens.empty() || isOperator(tokens.back())))) {
            number += ch;
        } else {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.emplace_back(1, ch);
        }
    }

    if (!number.empty()) {
        tokens.push_back(number);
    }

    return evaluateExpression(tokens);
}