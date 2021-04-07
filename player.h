#include <iostream>

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
    std::string username;
    int xp;
    int health;

public:
    Player(std::string username, int xp, int health);
    Player();
    Player(const Player &source);
    ~Player();

    void talk(std::string);
    bool is_dead();

    std::string getUsername();
    void setUsername(std::string);
    int getHealth();
};

#endif