#include <iostream>
using namespace std;

/* ADDENDUM FOR PROJECT MEMBERS*/
/*
This is the Lexer part of the program that I have now. The key points to know about it:
    > It iterates through the full input expression, but it only outputs one token at a time.
        - Turns out, creating an array of differing data types in C++ is not as simple as Python.
    > The Parser will need to take each token one at a time (I marked the output areas with obnoxious arrows, right now they just print)
        and slowly build up a data structure or whatever formatting method you guys have in mind.
    > Right now the Lexer just outputs the valid tokens, but it doesn't define their types.
        - This means everything the Parser receieves will actually just be strings.
        - I wasn't sure if you guys preferred working with the raw strings or Classes.
        - If it would be easier to have defined classes for these tokens. Let me know and I can make those as well.
    > An update tab will be put below to show how this program has changed since I wrote the above points.

    > P.S. From how I see it, we can either bulid off of this file or we can link individual files to each other. Whatever's easiest.
    > P.P.S. Please don't make fun of my code too much :')
*/

/* UPDATES */
/*
    > I have reworked how the output of this program works so now it can output a full expression instead of one token at a time.
        - That stuff I said above about differing data types in an array? Dumb. Everything that was being output was a string.
*/

int main(){
    // Grab the input string
    string input;
    cout << "For now, input an expression here: ";
    getline (cin, input);
    // Uncomment below if you just want to see the full input line.
    // cout << "The expression is: " << input << endl;
    // Iterate through string
    string token = "";
    string expression = "";
    bool isNumber = false; // This will check later to see if we are currently building a number or not.
    for (int i = 0; i < input.length(); i++){ // "Tokenize" each character
        // We'll need these booleans later. Helps avoid errors.
        bool operatorMade = false;
        bool parenthesisMade = false;
        // We'll check first to see if the character is a number...I'm going to use a sort of "digits bank"
        string digits = "1234567890";
        for (int j = 0; j < digits.length(); j++){
            if ((input[i] == digits[j]) && !(isNumber)){ // If the char is any of the digits and we're not currently building a number. Start!
                token = "";
                token += input[i]; // We add the digit to the running number.
                isNumber = true; // Then we enable numberSpotted to keep building for successive digits.
                break;
            }
            else if ((input[i] == digits[j]) && (isNumber)){ // If the char is a digit and we're currently building a number. Continue.
                token += input[i];
                break;
            }
            if ((j == (digits.length() - 1)) && (isNumber)) { // If all the digits were iterated through and the expression is no longer a number. Stop.
                isNumber = false;
                expression += token; // <<<<<<<<<<<<<<<<<<<<<<<< THIS IS WHERE A NUMBER TOKEN IS SENT OUT
                break;
            }
        }
    
        if (isNumber){ // Are we in the middle of building a number?
            continue; // Go to next iteration to check for another digit.
        }

        // If the token isn't a number, we'll check if it's an operator.
        string operators = "+-*/%";
        for (int j = 0; j < operators.length(); j++){
            if (input[i] == operators[j]) {
                if (input[i] == operators[2]){
                    if (i+1 < input.length()){ // We need a few "checks" here because an error could occur...
                        if (input[i+1] == operators[2]){
                            token = "**";
                            i++; // Increment i so we don't count the multiplication symbol again
                            expression += token; // <<<<<<<<<<<<<<<<<<< THIS IS WHERE AN OPERATOR TOKEN IS SENT OUT
                            operatorMade = true;
                            break;
                        }
                    }
                }
                token = operators[j];
                expression += token; // <<<<<<<<<<<<<<<<<<<<<< THIS IS WHERE AN OPERATOR TOKEN IS SENT OUT
                operatorMade = true;
                break;
            }
        }
    
        if (operatorMade){ // This is so we can avoid the error net at the bottom of the for-loop.
            continue;
        }

        // Now that operators have been accounted for, we just need to check if the character is a parenthesis or not.
        string parentheses = "()";
        for (int j = 0; j < parentheses.length(); j++){
            if (input[i] == parentheses[j]){
                token = parentheses[j];
                expression += token; // <<<<<<<<<<<<<<<<<<<<<< THIS IS WHERE A PARENTHESIS TOKEN IS SENT OUT
                parenthesisMade = true;
                break;
            }
        }

        if (parenthesisMade){ // Avoid the for-loop error at the bottom.
            continue;
        }
        
        // Any white space we simply skip past.
        string space = " "; 
        if (input[i] == space[0]){
            continue;
        }

        // If the loop ever gets this far without breaking or iterating, that must mean the token is invalid.
        cout << "Invalid token in expression." << endl; // <<<<<<<<<<<<<<<<< RAISE AN ERROR!
        break;
    }

    // At the very end, after the for loop, we have to check if there was a number that never marked as "finished"
    if (isNumber){
        expression += token;
    }
    
    // Our official expression, barring any error occurring is below.
    cout << expression << endl; // <<<<<<<<<<<<<<<<<<<<< THIS IS WHAT YOU GUYS SHOULD USE
}

 // Pass each token to Parser