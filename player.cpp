#include "player.h"


Player::Player(std::string name, int xp, int health)
    : username{name}, xp{xp}, health{health} {
}
Player::Player()
    : username{"None"}, xp{0}, health{0} {
}
Player::Player(const Player &source)
    : username{source.username},
      xp{source.xp},
      health{source.health} {
          
    std::cout << "A copy is made" <<std::endl;
}
Player::~Player(){};


void Player::talk(std::string s) { std::cout<< s <<std::endl; }
bool Player::is_dead() { return (this->xp < 1) ? true : false; }

std::string Player::getUsername() { return this->username; }
int Player::getHealth() { return this->health; }
void Player::setUsername(std::string uname) { this->username = uname; }