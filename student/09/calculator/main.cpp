#include "calculations.hh"
#include <iostream>
#include <iomanip>
#include <sstream>  // for implementing function string_to_double
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const string GREETING_AT_END = "Thanks and see you later!";

// Utility function to sections a string at delimiters
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// Function string_to_double changes a string comprising a real number
// into a float type value for calculations.
// It returns true, if parameter s comprised a real.
// It returns false, if s was not a valid real number.
// The converted float will be assigned into reference parameter result.
// The implementation of the function uses stringstream for the sake of example.
bool string_to_double(const string& s, double& result);


// TODO: Explore the following data structures!
struct Command {
    string str;
    vector<string>::size_type parameter_number;
    bool is_exit;
    double(*action)(double, double);
};

const vector<Command> COMMANDS = {
    {"+", 2, false, addition},
    {"-", 2, false, subtraction},
    {"*", 2, false, multiplication},
    {"/", 2, false, division},
    {"PLUS", 2, false, addition},
    {"MINUS", 2, false, subtraction},
    {"TIMES", 2, false, multiplication},
    {"DIVIDED", 2, false, division},
    {"ADDITION", 2, false, addition},
    {"SUBTRACTION", 2, false, subtraction},
    {"MULTIPLICATION", 2, false, multiplication},
    {"DIVISION", 2, false, division},
    {"SUM", 2, false, addition},
    {"DIFFERENCE", 2, false, subtraction},
    {"PRODUCT", 2, false, multiplication},
    {"QUOTIENT", 2, false, division},
    {"ADD", 2, false, addition},
    {"INCREASE", 2, false, addition},
    {"SUBTRACT", 2, false, subtraction},
    {"DECREASE", 2, false, subtraction},
    {"MULTIPLY", 2, false, multiplication},
    {"DIVIDE", 2, false, division},
    {"^", 2, false, pow}, // Add the "^" command for exponentiation
    {"POWER", 2, false, pow},
     {"EXP", 2, false, pow},
    {"STOP", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr}
};


int main() {

    // Using precision of two decimals in printing
    cout.precision(2);
    cout << fixed;

    while ( true ) {
        cout << "calculator> ";

        string line = "";
        getline(cin, line);

        if ( line.empty() ) {
            // By inputting an empty line, the user can make the program end.
            cout << GREETING_AT_END << endl;
            break;
        }

        vector<string> pieces = split(line, ' ', true);

        if(pieces.size() == 0){
            continue;
        }

        string command_to_be_executed = pieces.at(0);

        // TODO: Implement command execution here!
        transform(command_to_be_executed.begin(), command_to_be_executed.end(), command_to_be_executed.begin(), ::toupper);

               auto it = find_if(COMMANDS.begin(), COMMANDS.end(), [command_to_be_executed](const Command& cmd) {
                   return cmd.str == command_to_be_executed;
               });

               if (it != COMMANDS.end()) {
                   if (!it->is_exit) {
                       if (pieces.size() - 1 == it->parameter_number) {
                           double operand1, operand2;
                           if (string_to_double(pieces.at(1), operand1) && string_to_double(pieces.at(2), operand2)) {
                               double result = it->action(operand1, operand2);
                               cout <<  result << endl;
                           } else {
                               cout << "Error: a non-number operand." << endl;
                           }
                       } else {
                           cout << "Error: wrong number of parameters." << endl;
                       }
                   } else {
                       // Check if there are extra parameters after the exit command
                       if (pieces.size() > 1) {
                           cout << "Error: wrong number of parameters." << endl;
                       } else {
                           cout << GREETING_AT_END << endl;
                           break;
                       }
                   }
               } else {
                   cout << "Error: unknown command." << endl;
               }
           }

           return 0;
       }

// This function exemplifies istringstreams.
// It would be possible to use function stod of string to convert a string to
// a double, but to recognize all error cases would be more complicated with it
// at this phase of education.
// It is easier to use the boolean type return value that can be
// examined at calling point as done in the implementation below.
bool string_to_double(const string& s, double& result) {
    istringstream stream(s);
    double tmp;
    stream >> tmp;

    if (!stream) {
        return false;
    }

    stream >> ws;
    stream.get();

    if (stream) {
        return false;
    } else {
        result = tmp;
        return true;
    }
}

// Model implementation of good old split function
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
