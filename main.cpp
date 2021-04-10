#include <iostream>

#include "player.h"

int main() {
    std::cout << std::boolalpha <<std::endl;

    Player p {"player1234", 10, 5};
    std::cout << p.getUsername() <<std::endl;
    std::cout << p.getHealth() <<std::endl;

    Player p2 {Player{"ninja", 10, 5}};
    std::cout<< (p2 == p) <<std::endl;

    std::cout<< p2 <<std::endl;

    return 0;
}