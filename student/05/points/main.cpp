#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string filename = "";
    cout << "Input file: ";
    getline(cin, filename);

    ifstream inputFile(filename);
    if ( not inputFile ) {
        cout << "Error! The file " << filename<< " cannot be opened."<<endl;
        return 1;
    }
     map<std::string, int> playerScores;

     string playerName;
     string line;
     while (getline(inputFile, line)) {
         int colonPos = line.find(':');
         if (colonPos > 0) {
                    std::string playerName = line.substr(0, colonPos);
                    int points = std::stoi(line.substr(colonPos + 1));
                    playerScores[playerName] += points;
                }
         else{
             cout << "Error! Invalid line in input file: " << line << std::endl;
         }


     }

        inputFile.close();
          cout << "Final scores:" << std::endl;
          for (const auto& pair : playerScores) {
                  cout << pair.first << ": " << pair.second << std::endl;
              }

return EXIT_SUCCESS;

}
