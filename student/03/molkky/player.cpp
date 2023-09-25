// player.cpp

#include "player.hh"
using namespace std;
Player::Player(const string& name) : name(name), points(0), hasWon(false) {
    // Constructor sets the player's name, initializes points to 0, and hasWon to false
}

string Player::get_name() const {
    return name;
}

int Player::get_points() const {
    return points;
}

bool Player::has_won() const {
    return points >= 50;
}

void Player::add_points(int newPoints) {
    points += newPoints;
    if (points > 50) {
        points = 25; // Apply the penalty if points exceed 50
    }
    if (points >= 50) {
        hasWon = true;
    }
}
