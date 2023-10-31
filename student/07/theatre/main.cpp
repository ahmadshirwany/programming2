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


struct Play;

struct Theater{

    string city;
    string name;
    vector<Play> plays;

};

struct Play {
    string name ;
    string alias;
    bool has_alias = false;
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
bool hasAlias (string &play, string &alias){
    vector<string> parts = split(play, '/');
    if (parts.size()==2){
        play = parts.at(0);
        alias = parts.at(1);
        return true;

    }
    return false;

}
bool read_data(map<string,Theater> &theaters){
    string fileName;
    cout <<"Input file:";
    getline(cin, fileName);
    ifstream file(fileName);
    if(file){
        string line;
        while(getline(file,line)){
            vector<string> parts = split(line, ';');
             string town = parts.at(0);
            string theater = parts.at(1);
            string play = parts.at(2);
            string actor = parts.at(3);
            string seats = parts.at(4);
            if (theaters.find(theater)==theaters.end()){
                Theater t = Theater{town,theater, {}};
                theaters.insert({theater,t})  ;

            }
            Play p = Play();
            p.name = play;
            p.has_alias = hasAlias(p.name, p.alias);
            p.actor = actor;
            p.seat =  ("none" == seats)? 0 :stoi(seats);
            theaters.at(theater).plays.push_back(p);

            }
        file.close();
        }
    else{
        return false;
    }

    return true;

    }
void print_theaters(map<string,Theater> const &theaters){
    for (pair<string, Theater> const &t : theaters){
        cout<< t.first << endl;
    }
}
void print_plays_in_theater(map<string,Theater> const &theaters,const string theatername){
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
        cout << "Error: unknown play"<<endl;
    }
    else{
   for (const string& playName : uniquePlayNames) {
          cout << playName << std::endl;
      }
    }

}
bool compareTheaterNames(const Theater& theater1, const Theater& theater2) {
    return theater1.name < theater2.name;
}
bool comparePlayNames(const Play& play1, const Play& play2) {
    return play1.name < play2.name;
}
void print_plays_in_town(map<string,Theater> const &theaters,const string city){
    std::vector<Theater> theatersInCity;
       for (const auto& theaterPair : theaters) {
           const Theater& theater = theaterPair.second;
           if (theater.city == city) {
               theatersInCity.push_back(theater);
           }
       }
      std::sort(theatersInCity.begin(), theatersInCity.end(), compareTheaterNames);
      for (const Theater& theater : theatersInCity) {
              std::vector<Play> playsWithFreeSeats;
              for (const Play& play : theater.plays) {
                  if (play.seat > 0) {
                      playsWithFreeSeats.push_back(play);
                  }
              }
              std::sort(playsWithFreeSeats.begin(), playsWithFreeSeats.end(), comparePlayNames);
               if (!playsWithFreeSeats.empty()) {
                      for (const Play& play : playsWithFreeSeats) {
                          if (!play.alias.empty()) {
                              cout<< theater.name<<" : "<<play.name<<" -- "<<play.alias <<" : "<<play.seat<<endl;
                          }
                          else{
                              cout<< theater.name<<" : "<<play.name<<" : "<<play.seat<<endl;

                          }
                      }
               }
               else{
                   cout << "No plays available"<<endl;
               }


                  }


}

void print_theaters_of_play(map<string,Theater> const &theaters,const string playname){
     vector<string> playNames;
    for (const auto& theaterPair : theaters) {
            const Theater& theater = theaterPair.second;

            for (const Play& play : theater.plays) {
                // Check if the play name matches the provided playName
                if (play.name == playname || play.alias == playname) {
                    playNames.push_back(theater.name) ;

                }
            }
        }
    sort(playNames.begin(), playNames.end());
    set<string> uniquePlayNames(playNames.begin(), playNames.end());
     if (uniquePlayNames.empty()) {
         cout << "Error: unknown play"<<endl;
     }
     else{
    for (const string& playName : uniquePlayNames) {
           cout << playName << std::endl;
       }
     }

}

void print_plays(map<string,Theater> const &theaters){
    vector<string> playNames;
    for (const auto& theaterPair : theaters) {
           const Theater& theater = theaterPair.second;

           for (const Play& play : theater.plays) {
               // Print alias with " *** " separator if available
               if (!play.alias.empty()) {
                   playNames.push_back(play.name+"***"+play.alias);
               }
               else{
                    playNames.push_back(play.name);

               }
           }
       }
    sort(playNames.begin(), playNames.end());
    set<string> uniquePlayNames(playNames.begin(), playNames.end());
    for (const string& playName : uniquePlayNames) {
           cout << playName << std::endl;
       }
   }



// Main function
int main()
{
    map<string, Theater> theaters;
    bool check;
    check = read_data(theaters);
    if (!check){
        cout<<"Error: input file cannot be opened"<<endl;
        return EXIT_SUCCESS;

    }
    string cmd;
    while(true){
        cout<< PROMPT;
        getline(cin,cmd);
        if (cmd == "quit"){
              return EXIT_SUCCESS;
        }
        if (cmd == "theaters"){
            print_theaters(theaters);
            continue;
        }
        if (cmd == "plays"){
            print_plays(theaters);
            continue;
        }
         if (cmd.find(" ") != std::string::npos) {

              vector<string> cmd_vec = split(cmd,' ');

             if (cmd_vec.at(0)=="theaters_of_play"){
                 size_t found = cmd.find("\"");
                 if (found != std::string::npos) {
                      vector<string> cmd_vec;
                      size_t firstDoubleQuote = cmd.find("\"");
                      size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                      std::string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                      print_theaters_of_play(theaters,extractedSubstring);
                 }
                 else{
                  print_theaters_of_play(theaters,cmd_vec.at(1));
                 }
             }
             if (cmd_vec.at(0)=="plays_in_theater"){
                 size_t found = cmd.find("\"");
                 if (found != std::string::npos) {
                      vector<string> cmd_vec;
                      size_t firstDoubleQuote = cmd.find("\"");
                      size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                      std::string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                      print_plays_in_theater(theaters,extractedSubstring);
                 }
                 else{
                  print_plays_in_theater(theaters,cmd_vec.at(1));
                 }

             }
             if (cmd_vec.at(0)=="plays_in_town"){
                 size_t found = cmd.find("\"");
                 if (found != std::string::npos) {
                      vector<string> cmd_vec;
                      size_t firstDoubleQuote = cmd.find("\"");
                      size_t secondDoubleQuote = cmd.find("\"", firstDoubleQuote + 1);
                      std::string extractedSubstring = cmd.substr(firstDoubleQuote + 1, secondDoubleQuote - firstDoubleQuote - 1);
                      print_plays_in_town(theaters,extractedSubstring);
                 }
                 else{
                  print_plays_in_town(theaters,cmd_vec.at(1));
                 }

             }

         }
    }
    return EXIT_SUCCESS;
}
