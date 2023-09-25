#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
using namespace std;
class Player {
public:
    Player(const string& name); // Constructor
    string get_name() const;
    int get_points() const;
    bool has_won() const;
    void add_points(int points);

private:
    string name;
    int points;
    bool hasWon;
};
#endif // PLAYER_HH
