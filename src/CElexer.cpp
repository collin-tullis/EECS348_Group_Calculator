#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Lexer {
public:
    const string operators = "+-*/%.()";

    vector<string> createToken(string input) 
    {
        vector<string> tokens;
        string expression = "";
        bool isNumber = false;
        double num = 0.0;

        for (size_t i = 0; i < input.length(); i++) 
        {
            char c = input[i];
            if (isdigit(c)) 
            {
                int numAdd = c - '0';
                num = (num * 10) + numAdd;
                isNumber = true;
                continue;
            }

            if (isNumber) 
            {
                tokens.push_back(to_string(num));
                num = 0.0;
                isNumber = false;
            }

            if (operators.find(c) != string::npos) 
            {
                if (c == '*' && i + 1 < input.length() && input[i + 1] == '*') 
                {
                    tokens.push_back("**");
                    i++; // Skip the second '*'
                } else 
                {
                    tokens.push_back(string(1, c));
                }
            }
            else if(!isdigit(c) && c != ' ')
            {
                cout << "You stupid"; //todo error handling
            }
        }

        if (isNumber) 
        {
            tokens.push_back(to_string(num));
        }

        return tokens;
    }
};

int main() {
    Lexer mypar;
    string input;
    cin >> input;
    vector<string> result = mypar.createToken(input);

    for (const string& token : result) {
        cout << token << " ";
    }

    return 0;
}
