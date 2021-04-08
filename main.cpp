#include <iostream>

#include "player.h"

int main() {
        
    Player p {"player1234", 10, 5};
    std::cout << p.getUsername() <<std::endl;
    std::cout << p.getHealth() <<std::endl;

    Player p2 {Player{"ninja", 10, 5}};

    return 0;
}