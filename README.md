# Stack and Heap Memory
Stack memory is for regular operations and stores temporary variables. Nothing fancy.  
  
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

.h class declaration example using the 4 pillars : attributes / constructors-destructor / methods / getters-setters  
some good practices:
- if your method won't modify the object, tell the compiler that it won't using the const qualifier after the function declaration (getters usually)  
- implement a move constructor (but not here. see Move constructor section)
```cpp
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
    std::string username;
    int xp;
    int health;

public:
    Player(std::string username, int xp, int health);
    Player();
    Player(const Player &source); // copy constructor, but later (Move constructor section) there is a better way.
    ~Player();

    void talk(std::string) const;
    bool is_dead() const;

    std::string getUsername() const;
    void setUsername(std::string);
    int getHealth() const;
};
#endif

```
.cpp class implementation of the class declaration

```cpp
#include "player.h"


Player::Player(std::string name, int xp, int health)
    : username{name}, xp{xp}, health{health} {
}
Player::Player()
    : username{"None"}, xp{0}, health{0} {
}
Player::Player(const Player &source)
    : username{source.username}, xp{source.xp}, health{source.health} {
          
    std::cout << "A copy is made" <<std::endl;
}
Player::~Player(){
    // if we have a pointer data or a raw array as attribute we would write
    delete data;
    delete [] array_ptr; // for a raw array
};


void Player::talk(std::string s) const { std::cout<< s <<std::endl; }
bool Player::is_dead() const { return (this->xp < 1) ? true : false; }

std::string Player::getUsername() const { return this->username; }
int Player::getHealth() const { return this->health; }
void Player::setUsername(std::string uname) { this->username = uname; }
```
  
# Move constructor (The C++ Move semantic) - More advanced
In some projects we tend to pass our object in functions or initialize another object using the existing object, anyway we tend to use the copy constructor. And this can be very computationnaly innefficient. To handle this, we have the move constructor. It allows us to "move" or "displace" the constructor without copying and this is VERY computationally efficent and possible since C++11.

```cpp
// Move constructor implementation (note the r-value reference &&)
Player::Player(Player &&source)
    : username{source.username}, xp{source.xp}, health{source.health} {
          
    std::cout << "Moved" <<std::endl; // may not printed
}
```
  
In case you have a pointer (called data) as attribute, a deepcopy is required (not so efficient) using the copy constructor:

```cpp
// COPY CONSTRUCTOR FOR DEEPCOPYING THE POINTER
Person::Player(const Player &source)
    : a{source.a}, b{source.b}, c{source.c} {

    int *data = new int;
    *data = source.data;
}
```
But much more efficient and easy to do with the move constructor:
```cpp
// USING MOVE CONSTRUCTOR
Player::Player(Player &&source)
    : a{source.a}, b{source.b}, c{source.c}, data{source.date} {

    source.data = nullptr;
}
```
In many ressources we can read that the move constructor "Steal" the data then nulls out the source.  
So if we call `myvector.push_back(Player{"", 3, 4})` this will call the move constructor because we have a reference R-value as argument.  
But if for example we do:   
```cpp
Player p {"", 3, 4};
myvector.push_back(p);
```
This will call the copy constructor because at this point player is an L-value.

### Note on static class members
Static variables share class-wide information. They belong to the class and not on a signe object of that class. For example, if we have multiples instances of the same class (instances), we can use static attribute to share this information.  
Let's say we want to count the number of instances of that class. We can create a static variable that will be incremennted by one in the constructor and decremented by one in the destructor.  
- They are independant of the object
- It makes sense to call them using the class name directly
```cpp

// class declaration in .h
class Player {
    static int num_players;

public:
    Player();
    ~Player();
    static int getNumPlayer();
};

// class implementation in .cpp
int Player::num_players {0};

Player::Player(){
    num_players++
}
Player::~Player(){
    --num_players
}
int Player::getNumPlayer(){
    return num_players; 
}

// call in main
int main(){
    std::cout << Player::getNumPlayer() <<std::endl;
    return 0;
}
```
## Operator Overloading
```cpp
// overloaded operators declaration in .h
bool operator==(const Player &rhs) const;

// overloaded operators implementation in .cpp
bool Player::operator==(const Player &rhs) const{
    if(xp == rhs.xp && health == rhs.health)
        return true;
    return false;
}
```
to overload the insertion (cout) operator it should be done in the private section of the class.  

```cpp
// overloaded insertion declaration in .h
class Player {
    std::string username;
    int xp;
    int health;
    friend std::ostream &operator<<(std::ostream &os, const Player &obj);
};

// implementqtion in .cpp
std::ostream &operator<<(std::ostream &os, const Player &obj){
    os << obj.username;
    // os << obj.getUsername(); if it was'nt a friend
    return os;
}
```

## Inhirithance
## Polymorphism
# Exception handling
# Files I/O and Streams
# STL
# Use arguments in main
# C++ Unit tests
# CMake : Build C++ projects