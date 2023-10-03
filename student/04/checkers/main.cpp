#include "gameboard.hh"
#include <iostream>
#include "gameboard.hh"
#include <sstream>
#include <limits>

using namespace std;
bool is_digits(string& str)
{
    for (char ch : str) {
         // ASCII Val converted
        if (ch == ' ') {
                    // Ignore spaces
                    continue;
                }
        if (!(ch >= 48 && ch <= 57)) {

            return false;
        }
    }

    return true;
}

int main()
{
   char pieceChar;
   cout << "Enter piece character: ";
   cin >> pieceChar;
   vector<int> cor ;
   GameBoard gameb = GameBoard(pieceChar);
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   gameb.print();
    while (true) {
       cor.clear();
       cout << "Enter start and destination points (e.g., 12 34) or q to quit: ";
       string moveInput ;
       std::getline(std::cin, moveInput);

       if (moveInput == "q") {
           gameb.print_moves();
           break;
       }
       if (moveInput.size()!=7){
           cout<<"Invalid start/destination point."<<endl;
           continue;
       }
       if (!is_digits(moveInput)){
            cout<<"Invalid start/destination point."<<endl;
            continue;
       }

       vector<int> cor ;
        for (unsigned int i = 0; i < moveInput.size(); i++) {
            if (moveInput[i] == ' ') {
                // Ignore spaces
                continue;
            }
            else{
                cor.push_back( int(moveInput[i]) - 48);
            }
        }
       if (cor.size()!=4){
            cout<<"Invalid start/destination point."<<endl;
             continue;
       }
       if (gameb.isvalidinput(cor)){
           cout<<"Invalid start/destination point."<<endl;
            continue;
       }

       if (!gameb.isvalidmove(cor)){
            cout<<"Invalid start/destination point."<<endl;
             continue;
       }
       gameb.makemove(cor);
    }

   return 0;
}
