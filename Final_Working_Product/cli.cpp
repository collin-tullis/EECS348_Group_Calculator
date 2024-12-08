/*
Command Line Interface
Description: Components of a command line interface
*/
/*
So i messed with different gui packages for like 3 hours and coudn't 
even create a window, so command line interface it is
*/
#include <iostream>
#include <string>
#include "evaluator.cpp"
#include "CEerrorcheck.cpp"
#include "CElexer.cpp"


using namespace std;

void PrintTitle(){
    //Print the title to the console
    cout << "                                      _________ \n";
    cout << "                                     | _______ |\n";
    cout << " ------------------------------      ||_______||\n";
    cout << "|                              |     |         |\n";
    cout << "|      Big Ole Calculator      |     | 7 8 9 / |\n";
    cout << "|                              |     | 4 5 6 * |\n";
    cout << " ------------------------------      | 1 2 3 - |\n";
    cout << "                                     |   0   + |\n";
    cout << "                                     |_________|\n";
}

void PrintDirections(){
    //Print the directions to the console
    cout << " Directions: Enter a mathematical Expression    \n"; 
    cout << " using integers, and the symbols provided in the\n";
    cout << " key.                                           \n";
}

void PrintKey(){
    //Print the key to the console
    cout << "                ________________                \n";
    cout << "               |      Key:      |               \n";
    cout << "               | Add      = +   |               \n";
    cout << "               | Subtract = -   |               \n";
    cout << "               | Multiply = *   |               \n";
    cout << "               | Divide   = /   |               \n";
    cout << "               | Modulo   = %   |               \n";
    cout << "               | Exponent = **  |               \n";
    cout << "               |________________|               \n";
}

string GetInput(){
    //Get an expression from the user
    string calculation;
    cout << "> Your Expression: ";
    cin >> calculation;
    return calculation;
}

void PrintInput(string input){
    //Print the input for debugging purposes
    cout << "> Your Input: " << input << "\n";
}

void PrintSolution(double solution){
    // Print the solution to the expression
    // I made it a float because I assume some of the expressions will result in a non integer value
    cout << "> Solution: " << solution << "\n";
}

void Space(int size = 1){
    //Space out the UI elements
    for (int i = 0; i < size; i++){
        cout << "\n";
    }
}

int main(){
    //Test all the functions to make sure they work properly
    
    PrintTitle();
    PrintKey();
    Space();
    PrintDirections();
    Space();
    string input = GetInput();
    Space();
    PrintInput(input);
    /*
    PrintSolution(6); //6 is arbitrary, just making sure it works
    Space();
    return 0;
    */

   Lexer lexer;
   ErrorHandler errorhandler;
   Evaluator evaluator;
   
   vector<string> lex_result = lexer.createToken(input);
    /*
   for (const string& token : lex_result) {
        cout << token << " ";
    }
    */

   if(errorhandler.error(lex_result)){
        double result = evaluator.evaluateExpression(lex_result);
        PrintSolution(result);
   }//else{
      //  cout << "Invalid expression for cli" << endl;
   //}
   return 0;

}