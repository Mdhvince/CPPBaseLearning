#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>



int main() {

    // placeholders
    int num {70};
    float total {100.57};
    std::string name {"Larry"};

    std::string data_from_user {"Larry 70 100.57"};

    // create an output stream
    std::ostringstream oss {};

    // variables are written into the stream. Can be useful to transfer data
    oss << std::setw(10) << std::left << name
        << std::setw(10) << num
        << std::setw(10) << total
        << std::endl;
    
    std::cout<< oss.str() <<std::endl;

    return 0;
}