#include <vector>
#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH
using namespace std;


// Pelilaudan koko
// Size of the gameboard
const unsigned int SIZE = 8;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa
// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard-luokka
// GameBoard class
class GameBoard
{
public:
    // Rakentaja: tarvittaessa voit lisätä parametreja
    // Constructor: you can add parameters if needed
    GameBoard(char pieceChar );
    struct Point {
            unsigned int x;
            unsigned int y;
        };

    // Tulostaa pelilaudan (kunhan olet viimeistellyt metodin).
    // Prints the gameboard (after you have finished the method).
    void print() const;
    void print_moves() const;
    bool isvalidmove(vector<int> cor);
    bool isvalidinput(vector<int> cor);
    void makemove(vector<int> cor);


private:
    // Tulostaa annetun pituisen rivin annettua tulostumerkkiä.
    // Prints a line with the given length and fill character.
    void initialize_cordinate();
    char pieceChar;
    vector<Point> cordinates;
    void print_line(unsigned int length, char fill_character) const;
    int moves;
};

#endif // GAMEBOARD_HH
