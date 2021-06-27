#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>


int main() {

    std::vector<int> v {1, 5, 3, 2, 10, 12, 3, 4, 6, 9};
    std::vector<int> v_square;
    std::vector<int> v_even;


    std::transform(v.begin(), v.end(), std::back_inserter(v_square), [](int &n) { return n * n; });
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_even), [](const int &n) { return n % 2 == 0; });
    
    std::for_each(v.begin(), v.end(), [](const int &n) { std::cout << n << "  ";});
    std::cout << std::endl;
    std::for_each(v_square.begin(), v_square.end(), [](const int &n) { std::cout << n << "  ";});
    std::cout << std::endl;
    std::for_each(v_even.begin(), v_even.end(), [](const int &n) { std::cout << n << "  ";});
    std::cout << std::endl;

    

    
    
    

    return 0;
}