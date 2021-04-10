#include <iostream>

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
    std::string username;
    int xp;
    int health;

    friend std::ostream &operator<<(std::ostream &os, const Player &obj);

public:
    //constructors/destructor
    Player(std::string username, int xp, int health);
    Player();
    Player(const Player &source);
    Player(Player &&source);
    ~Player();

    //methods
    void talk(std::string) const;
    bool is_dead() const;

    // getters/setters
    std::string getUsername() const;
    void setUsername(std::string);
    int getHealth() const;

    // overloaded operators
    bool operator==(const Player &rhs) const; 
};

#endif