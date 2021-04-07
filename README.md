# Stack and Heap Memory
To complete  
  

The heap memory can be reffered as a free store, we can put/Allocate as much things, objects, images as we want (well be reasonable, there is a limit - otherwise we can cause a memory leak). But we need extra care because the heap memory is also a LIFETIME memory, so we have to free this memory when we are done with it. If we have an array but we do not know how big it is gonna be at runtime, it could be a good idea to allocate its memory dynamically on the heap (see section on dynamic memory allocation for more).

# Pointers
It's just a variable pointing to another variable or function.  
The pointer stores the adress (memory location) of the pointed variable. So the value of a pointer, is an adress.  
Synthax :  
```cpp
double ptr_first {nullptr};                                                // a pointer that point nowhere. best practice is to do so while waiting a var to point on
int score {10};
int *ptr_score {&score};                                                   // point to the adress of score

std::cout << "Adress of the pointed variable: " << ptr_score <<std::endl;
std::cout << "Value of the pointed variable: " << *ptr_score <<std::endl;  // 10 - This is called dereferencing the pointer

*ptr_score = 67;                                                           // this change the value of score via the pointer

float note {5.5};
float *const ptr_note {&note};                                             // note can be changed, but the pointer not (cannot point to another variable)

```
## Dynamic memory Allocation
```cpp
int *int_ptr {nullptr};
int_ptr = new int;               // Allocate an Integer on the heap

int *array_ptr {nullptr};
size_t size {100000};            // User enter a size at runtime (ie using cin)
array_ptr = new int[size];       // Allocate an n Integers on the heap


// I you Allocate, You MUST deallocate
delete int_ptr;
delete [] array_ptr;
```
# OOP
I always thinking of 4 main blocks when defining a class:  
- Attributes
- Constructors / Destructor
- Methods
- Getters and Setters
  
Tip : If a multiple .cpp files include the same .h file, so in general if a .h file is included more n times in a project, the compiler will process it n times and give us an duplicate declaration error, to avoid this we need to tell the compiler to only process it once. We do that by wrapping an include guard around the class declaration.  
```cpp
#ifndef _CLASSNAME_H_
#define _CLASSNAME_H_
/*
    class declaration
*/
#endif
```

# CMake : Build c++ projects