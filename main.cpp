#include <iostream>


int main(int argc, char const *argv[]) {
    
    int *int_ptr {nullptr};
    int_ptr = new int;               // Allocate an Integer on the heap

    int *array_ptr {nullptr};
    size_t size {100000};            // User enter a size at runtime (ie using cin)
    array_ptr = new int[size];       // Allocate an n Integers on the heap


    
    // I you Allocate, You MUST deallocate
    delete int_ptr;
    delete [] array_ptr;
}
