#include "gameboard.hh"
#include <iostream>
#include <algorithm>

GameBoard::GameBoard(char pieceChar ): pieceChar(pieceChar)
{
    initialize_cordinate();
    moves = 0;
}
void GameBoard::initialize_cordinate(){
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            if  (i>=2 &&i <6 &&j>=2 &&j <6  ){

            } else{
               cordinates.push_back({i, j});
            }

}
    }
}



void GameBoard::print() const
{
    // Tulostetaan yläreuna
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    // Printing the actual content of the gameboard
    for(unsigned int j = 0; j < SIZE; ++j)
    {
        std::cout << "| " << j + 1 << " | ";
        for(unsigned int i = 0; i < SIZE; ++i)
        {
            // TODO:
            // Tulosta tässä tyhjä tai pelilaudan alkio (i, j)
            // Print here empty or the element (i, j) in the gameboard
            bool check = false;
             for( auto cordinate : cordinates ){
                 if (cordinate.x == i && cordinate.y==j){
                     check= true;

                 }

             }
             if (check){
                 std::cout << pieceChar<<" ";
             }
             else{
                  std::cout << " "  <<" ";
             }
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}


void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}
