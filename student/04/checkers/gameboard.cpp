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


bool GameBoard::isvalidinput(vector<int> cor){
     bool check = false;
     for (const int a :cor ){
         if (a>0&&a<9){


         }
         else{
             check = true;
             break;
         }
     }
     return check;

}

bool GameBoard::isvalidmove(vector<int> cor){
    bool start_check = false;
    for (const Point& p : cordinates) {
           if (p.x+1 == (unsigned int)cor[0] && p.y+1 == (unsigned int)cor[1]) {
               start_check = true;
               break; // Stop searching once found
           }
       }
    if (start_check == false){
        return start_check;
    }
    bool destination_check = false;
    for (const Point& p : cordinates) {
           if (p.x+1 == (unsigned int)cor[2] && p.y+1 == (unsigned int)cor[3]) {
               destination_check = true;
                cout<<"destination point"<<endl;
               break; // Stop searching once found
           }
       }
    if (destination_check == true){
        return false;
    }
    int a = cor[0]-cor[2];
    if (a<0){
        a =-a;
    }
    int b = cor[1]-cor[3];
    if (b<0){
        b =-b;
    }
    if(!(a==b)){
        return false;
    }
    if (!((a < 3 && a > 0) && (b< 3 && b>0))){
        return false;
    }

    unsigned int midx= (cor[0]+cor[2])/2;
    unsigned int midy = (cor[1]+cor[3])/2;
    bool mid_cor_check = false;
    for (const Point& p : cordinates) {
           if (p.x+1 == midx && p.y+1 == midy) {
               mid_cor_check = true;
               break; // Stop searching once found
           }
       }
    if (!mid_cor_check){
         cout<<"mid point"<<endl;
        return false;
    }


return true;
}

void GameBoard::makemove(vector<int> cor){

    unsigned int midx= (cor[0]+cor[2])/2;
    unsigned int midy = (cor[1]+cor[3])/2;

    for(auto iter = cordinates.begin(); iter != cordinates.end(); ++iter){
        if(iter->x == (unsigned int)cor[0]-1 && iter->y == (unsigned int)cor[1]-1){
            iter = cordinates.erase(iter);
            break;
        }
    }
    for(auto iter = cordinates.begin(); iter != cordinates.end(); ++iter){
        if(iter->x == (unsigned int)midx-1 && iter->y == (unsigned int)midy-1){
            iter = cordinates.erase(iter);
            break;
        }
    }

    Point p3 = {(unsigned int)cor[2]-1,(unsigned int)cor[3]-1};
    cordinates.push_back(p3);
    moves++;
    print();


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
