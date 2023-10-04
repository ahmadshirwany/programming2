#include "gameboard.hh"
#include <iostream>
#include "gameboard.hh"
#include <sstream>
#include <limits>

using namespace std;

void string_to_vector(vector<int>& cor ,string moveInput){
    for (unsigned int i = 0; i < moveInput.size(); i++) {
        if (moveInput[i] == ' ') {
            // Ignore spaces
            continue;
        }
        else{
            cor.push_back( int(moveInput[i]) - 48);
        }
    }

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
       string moveInput ;
       cout << "Enter start point (x, y) and destination point (x, y), or q to quit: ";
       std::getline(std::cin, moveInput);
       if (moveInput == "q") {
           gameb.print_moves();
           break;
       }
       if (gameb.isvalidinput_string(moveInput)){
           cout<<"Invalid start/destination point."<<endl;
           continue;
       }


       vector<int> moving_cordinate ;
       string_to_vector(moving_cordinate,moveInput);


       if (gameb.isvalidcordinates(moving_cordinate)){
           cout<<"Invalid start/destination point."<<endl;
            continue;
       }

       if (!gameb.isvalidmove(moving_cordinate)){
            cout<<"Cannot move from start point to destination point."<<endl;
             continue;
       }
       gameb.makemove(moving_cordinate);
    }

   return 0;
}
