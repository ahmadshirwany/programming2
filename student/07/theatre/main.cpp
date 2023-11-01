#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

// Fields in the input file
const int NUMBER_OF_FIELDS = 5;

// Command prompt
const string PROMPT = "the> ";

// Define a structure for representing a Play
struct Play;

// Define a structure for representing a Theater
struct Theater{
    string city;
    string name;
    vector<Play> plays;
};

// Structure for representing a Play
struct Play {
    string name;
    string alias;
    bool has_alias = false; // Flag indicating if the play has an alias
    string actor;
    int seat;
};

// Error and other messages
const string EMPTY_FIELD = "Error: empty field in line ";
const string FILE_ERROR = "Error: input file cannot be opened";
const string WRONG_PARAMETERS = "Error: wrong number of parameters";
const string THEATRE_NOT_FOUND = "Error: unknown theatre";
const string PLAY_NOT_FOUND = "Error: unknown play";
const string PLAYER_NOT_FOUND = "Error: unknown player";
const string TOWN_NOT_FOUND = "Error: unknown town";
const string COMMAND_NOT_FOUND = "Error: unknown command";
const string NOT_AVAILABLE = "No plays available";

// Casual split function, if delim char is between "'s, ignores it.
vector<string> split(const string& str, char delim)
{
    vector<string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delim and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    return result;
}
// Function to check if a Play has an alias and extracts it
bool hasAlias(string &play, string &alias){
    vector<string> parts = split(play, '/');
    if (parts.size() == 2){
        play = parts.at(0);
        alias = parts.at(1);
        return true;
    }
    return false;
}

// Function to read data from an input file and populate the 'theaters' map
bool read_data(map<string,Theater> &theaters){
    string fileName;
    int count = 0;
    cout << "Input file: ";
    getline(cin, fileName);
    ifstream file(fileName);
    if(file){
        string line;
        while(getline(file, line)){
            count++;
            vector<string> parts = split(line, ';');
            bool hasEmptyString = false;

            for (const string& str : parts) {
                if (str.empty()) {
                    hasEmptyString = true;
                    break; // No need to continue checking once an empty string is found
                }
            }
            if (parts.size() < NUMBER_OF_FIELDS){
                hasEmptyString = true;
            }

            if (hasEmptyString) {
                cout << EMPTY_FIELD << to_string(count) << endl;
                return false;
            }
            string town = parts.at(0);
            string theater = parts.at(1);
            string play = parts.at(2);
            string actor = parts.at(3);
            string seats = parts.at(4);
            if (theaters.find(theater) == theaters.end()){
                Theater t = Theater{town, theater, {}};
                theaters.insert({theater, t});
            }
            Play p = Play();
            p.name = play;
            p.has_alias = hasAlias(p.name, p.alias);
            p.actor = actor;
            p.seat =  ("none" == seats) ? 0 : stoi(seats);
            theaters.at(theater).plays.push_back(p);
        }
        file.close();
    }
    else{
        cout << FILE_ERROR << endl;
        return false;
    }

    return true;
}
// Function to print the names of all theaters
void print_theaters(map<string,Theater> const &theaters){
    for (pair<string, Theater> const &t : theaters){
        cout << t.first << endl;
    }
}
// Function to print the names of all plays
void print_plays(map<string,Theater> const &theaters){
    vector<string> playNames;
    for (const auto& theaterPair : theaters) {
        const Theater& theater = theaterPair.second;

        for (const Play& play : theater.plays) {
            // Print alias with " *** " separator if available
            if (!play.alias.empty()) {
                playNames.push_back(play.name + " *** " + play.alias);
            }
            else{
                playNames.push_back(play.name);
            }
        }
    }
}
// Function to print the names of theaters where a specific play is performed
void print_theaters_of_play(map<string,Theater> const &theaters, const string playname){
    vector<string> playNames;
    for (const auto& theaterPair : theaters) {
        const Theater& theater = theaterPair.second;

        for (const Play& play : theater.plays) {
            if (play.name == playname || play.alias == playname) {
                playNames.push_back(theater.name);
            }
        }
    }
    sort(playNames.begin(), playNames.end());
    set<string> uniquePlayNames(playNames.begin(), playNames.end());
    if (uniquePlayNames.empty()) {
        cout << PLAY_NOT_FOUND << endl;
    }
    else{
        for (const string& playName : uniquePlayNames) {
            cout << playName << endl;
        }
    }
}
// Function to print the names of all plays in a specific theater
void print_plays_in_theater(map<string,Theater> const &theaters, const string theatername){
    vector<string> playNames;
    auto theaterIter = theaters.find(theatername);
    if (theaterIter != theaters.end()) {
        const Theater& theater = theaterIter->second;
        for (const Play& play : theater.plays) {
            playNames.push_back(play.name);
        }
    }
    sort(playNames.begin(), playNames.end());
    set<string> uniquePlayNames(playNames.begin(), playNames.end());
    if (uniquePlayNames.empty()) {
        cout << THEATRE_NOT_FOUND << endl;
    }
    else{
        for (const string& playName : uniquePlayNames) {
            cout << playName << endl;
        }
    }
}
// Main function
int main(){
    map<string, Theater> theaters;
    bool check;
    check = read_data(theaters);
    if (!check){
        return EXIT_FAILURE;
    }
    string cmd;
    while(true){
        cout << PROMPT;
        getline(cin, cmd);
        if (cmd == "quit"){
              return EXIT_SUCCESS;
        }
        else if (cmd == "theatres"){
            print_theaters(theaters);
            continue;
        }
        else if (cmd == "plays"){
            print_plays(theaters);
            continue;
        }
        else if (cmd.find(" ") != std::string::npos) {
            vector<string> cmd_vec = split(cmd, ' ');

            if (cmd_vec.at(0) == "theatres_of_play"){
                size_t found = cmd.find("\"");
                if (found != std::string::npos) {
                    vector<string> cmd_vec;
                    size_t firstDoubleQuote = cmd.find("\"");
                    size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                    string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                    print_theaters_of_play(theaters, extractedSubstring);
                }
                else{
                    print_theaters_of_play(theaters, cmd_vec.at(1));
                }
            }
            else if (cmd_vec.at(0) == "plays_in_theatre"){
                size_t found = cmd.find("\"");
                if (found != std::string::npos) {
                    vector<string> cmd_vec;
                    size_t firstDoubleQuote = cmd.find("\"");
                    size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                    string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                    print_plays_in_theater(theaters, extractedSubstring);
                }
                else{
                    print_plays_in_theater(theaters, cmd_vec.at(1));
                }
            }
            else if (cmd_vec.at(0) == "plays_in_town"){
                size_t found = cmd.find("\"");
                if (found != std::string::npos) {
                    vector<string> cmd_vec;
                    size_t firstDoubleQuote = cmd.find("\"");
                    size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                    string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                    print_plays_in_town(theaters, extractedSubstring);
                }
                else{
                    print_plays_in_town(theaters, cmd_vec.at(1));
                }
            }
            else if (cmd_vec.at(0) == "players_in_play"){
                if (cmd_vec.size() > 2){
                    size_t firstDoubleQuote = cmd.find("\"");
                    size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                    string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                    print_players_in_play(theaters, cmd_vec.at(1), extractedSubstring);
                }
                else{
                    print_players_in_play(theaters, cmd_vec.at(1));
                }
            }
            else if (cmd_vec.at(0) == "plays"){
                cout << WRONG_PARAMETERS << endl;
            }
            else{
                cout << COMMAND_NOT_FOUND << endl;
            }
        }
        else{
            cout << COMMAND_NOT_FOUND << endl;
        }
    }
    return EXIT_SUCCESS;
}
