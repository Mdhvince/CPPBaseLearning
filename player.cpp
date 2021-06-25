#include "player.h"


Player::Player(std::string name, int xp, int health)
    : username{name}, xp{xp}, health{health} {}

Player::Player()
    : username{"None"}, xp{0}, health{0} {}

Player::Player(const Player &source)
    : username{source.username}, xp{source.xp}, health{source.health} {
    std::cout << "A copy is made" <<std::endl;
}

Player::Player(Player &&source)
    : username{source.username}, xp{source.xp}, health{source.health} {
    std::cout << "Moved." <<std::endl;
}

Player::~Player(){};


void Player::talk(std::string s) const { std::cout<< s <<std::endl; }
bool Player::is_dead() const { return (this->xp < 1) ? true : false; }

std::string Player::getUsername() const { return this->username; }
int Player::getHealth() const { return this->health; }
void Player::setUsername(std::string uname) { this->username = uname; }

bool Player::operator==(const Player &rhs) const{
    if(xp == rhs.xp && health == rhs.health)
        return true;
    return false;
}


std::ostream &operator<<(std::ostream &os, const Player &obj){
    os << obj.username;
    // os << obj.getUsername(); if it was'nt a friend
    return os;
}
