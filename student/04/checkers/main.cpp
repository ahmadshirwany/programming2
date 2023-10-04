#include "gameboard.hh"
#include <iostream>
#include "gameboard.hh"
#include <sstream>
#include <limits>

using namespace std;

/* Checkers (for one player)
 *
 * Desc:
 *   This program implements a checkers game for one player. The size of
 * the gameboard is 8 x 8, and it will filled with empty spaces and
 * game pieces (character given by the user).
 *   At first, the gameboard is filled with pieces, but there is an
 * empty area of size 4 x 4 in the middle of the gameboard. The aim is to
 * remove pieces such that only one of them is left. A piece can be moved
 * diagonally over another piece, whereupon the piece that was skipped
 * will be removed.
 *   On each round, the user is asked for two points (four coordinates):
 * the piece to be moved and its target position. The program checks if
 * if the move is possible.
 *   The program terminates when there is only one piece left or if the
 * user gives a quitting command ('q' or 'Q'). In such case the program
 * prints the number of moves made and that of pieces left.
 *
 * Program author ( Fill with your own info )
 * Name: Ahmad Ali Khan shirwany
 * Student number: 151485383
 * UserID: vnahsh
 * E-Mail: ahmad.shirwany@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * I have created a Gameboard class that manages the game board for a checkers game.
 * Within this class, I utilize a vector of Points structures, each containing XY coordinates to represent filled spaces on the game board.
 * Users can interact with the game board by providing input to move game pieces.
 * The class handles various operations on the vector, such as piece movement and placement, and it can also display the current state of the game board with pieces located at specific coordinates.
 *
 * */

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
