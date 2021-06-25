#include <iostream>
#include <memory>

#include "player.h"


class DivideByZeroException: public std::exception{
public:
    DivideByZeroException() noexcept = default; // noexcept tells that this cannot raise an exection
    ~DivideByZeroException() = default;

    virtual const char *what() const noexcept{
        return "Can't divide by zero";
    }
};

float calculate_avg(int sum, int total){
    if(total == 0)
        throw DivideByZeroException{};
    return static_cast<float>(sum) / total;
}

int main() {
    /*std::cout << std::boolalpha <<std::endl; // display true/false instead of 1/0

    std::unique_ptr<Player> p = std::make_unique<Player>("player1234", 10, 5);
    std::cout << p->getUsername() <<std::endl;
    std::cout << p->getHealth() <<std::endl;*/

    
    float average {};
    try{
        average = calculate_avg(56, 0);
        std::cout<<"Average: "<< average <<std::endl;
    }
    catch(const DivideByZeroException &ex) {
        std::cerr <<ex.what()<<std::endl;
    }

    return 0;
}