# Stack and Heap Memory
Stack memory is for regular operations and stores temporary variables. The stack space is reserved at compile time but the data is allocated at runtime.  
  
The heap memory can be reffered as a free store, we can put/Allocate as much things, objects, images as we want (well, there is a limit - otherwise we can cause a memory leak). But we need extra care because the heap memory is also a LIFETIME memory, so we have to free this memory when we are done with it. If we have an array but we do not know how big it is gonna be at runtime, it could be a good idea to allocate its memory dynamically on the heap (see section on dynamic memory allocation for more).

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
I always think of 4 main blocks when defining a class:  
- Attributes
- Constructors / Destructor
- Methods
- Getters and Setters
  
Tip : If multiple .cpp files include the same .h file, so in general if a .h file is included  n times in a project, the compiler will process it n times and give us an duplicate declaration error, to avoid this we need to tell the compiler to only process it once. We do that by wrapping an include guard around the class declaration.  

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
In some projects we tend to pass our object in functions or initialize another object using the existing object, anyway we tend to use the copy constructor. And this can be very computationally innefficient. To handle this, we have use the move constructor. It allows us to "move" or "displace" the constructor without copying and this is VERY computationally efficent and possible since C++11.

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
Static variables share class-wide information. They belong to the class and not on a single object of that class. For example, if we have multiples instances of the same class (instances), we can use static attribute to share this information.  
Let's say we want to count the number of instances of that class. We can create a static variable that will be incremented by one in the constructor and decremented by one in the destructor.  
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
Main change: Attributes of the base class should be protected, not private.  

```cpp
class Base {
protected:
    // attr
public:
    Base();
    Base(int name);
    ~Base();
    //methods
};
```

Devived class: The access-specifier if private by default. We should choose between private public protected.  
- public : is-a relationship (most common)  
- private and protected : has-a relationship "Derived has a Base class"  
  
The derived class has access to the methods and protected attributes of the base class. So only declare its specialized methods,  its additional attributes if there is some. Overridding or Redefining Base class methods is also possible.  
  
Derived does __NOT__ inherit:  
- Base class constructors
- Base class destructor
- Base class overloaded operators : But can be invoked from derived
- Base class friend functions : But can be invoked from derived  
```cpp
class Derived: access-specifier Base {
    // as usual
    int derived_name;
public:
    Derived();
    Derived(int derived_name);
    ~Derived();

};

// class implementation of the Dirived class
Derived::Derived():
    : Base(), derived_name{"None"} {
}
Derived::Derived(int derived_name):
    : Base(derived_name), derived_name{derived_name} {
}
```
In both initialization, if we do not invoke the Base constructor in the initialization, the default Base constructor will be called.  
  
We can also call Base class methods inside a dirived methods if we need to:
```cpp
void Derived::myDerived(int a){
    a += 10;
    Base::myBase(a);
}
```
  
## Polymorphism
Two kind of polymorphism :  
- __Compile time__ / __early binding__ / __static binding__ polymorphism : Overloading Methods and Operators. This kind of polymorphism is the fastest, because it is done at compile time.
- __Run time__ / __late binding__ / __dynamic binding__ polymorphism : It is like assigning a different meaning to the same function at run time. This kind of pylymorphism occurs at runtime and gives allows us to have a more readable program.  
  
Requierements for dynqmic Polymorphism:
- Have Inhiritance
- Have a base class pointer or a base class reference `Player *p = new Player();`
- Have virtual functions and a virtual destructor

First declare the methods that should be overriden as virtual in the Base class and the virtual destructor.  
```cpp
class Player{
protected:
    // ...
public:
    // ...
    virtual void talk();
    virtual ~Player();
};
```

In the derived class, override the Base class function, the function should match exactly the base class function, otherwise this will be a redefinition (which is statically bound).  
the `virtual` keyword is not mandatory in the derived class but it is a good practice.  
To avoid errors between overriding or redefining, we can add the `override` keyword to make the compiler raise an error if we are not overrifing.

```cpp
class WeakPlayer: public Player{
private:
    // ...
public:
    // ...
    virtual void talk() override;
};
```
And now, Dynamic Polymorphism in action:
```cpp
int main(){
    Player *century = new WeakPlayer();
    century->talk(); // This will call the WeakPlayer version of talk
    delete century;
}
```
  
For a __better compiler optimization__ we can use the `final` specifier at a class level or function level.  
At class level : Prevent a class from being derived.  
```cpp
class MyClass final {/*...*/};
// or
class Derived final: public Base {/*...*/};
```
At function level : Prevent a function from being overriden.
```cpp
void myFunction() final;
```


# Smart Pointers
Note : We cannot do pointer arithmetic with them (++, -- etc.)  
We cqnnot copy it (for the unique ptr), we can move it instead using `std::move(ptr)`  

```cpp
#include <memory>

// make_unique is available sinc C++14 otherwise we could use ... = { new Player{"player1234", 10, 5} }
std::unique_ptr<Player> ptr = std::make_unique<Player>("player1234", 10, 5);
// or 
auto ptr = std::make_unique<Player>("player1234", 10, 5);
ptr.get()                                   // return the adress of the object pointed
ptr.reset()                                 // nulls out the pointer

std::shared_ptr<Player> sh_ptr1 = std::make_shared<Player>("player1234", 10, 5);
std::shared_ptr<Player> sh_ptr2 {sh_ptr1};  // now there a pointing to the same object (shared ownership)
sh_ptr1.use_count()                         // return nb of shared_ptr reffering to the same heap object (or sh_ptr2.use_count())

```



# Exception handling
Should be used in synchronous code, not async.  
Terminology:  
- Exception Object: it signals when an error has occured
- Throwing/raising an exception: code that detects that an exception hase occured or will occur.
It describes the error to another part of the program that know how to handle the error.
- Catching/Handling an exception: code that handles the exception (May or may not cause the program to terminate)  
  
Synthax:  
- We try
- We throw an object by value
- We catch by reference (or const reference)
```cpp

float calculate_avg(int sum, int total){
    if(total == 0)
        throw 0;
    if(total < 0)
        throw std::string {"Negative value error"};

    return static_cast<float>(sum) / total;
}

// raise exception for 0 division
float average {};
try{
    average = calculate_avg(56, 100)
    std::cout<<"Average: "<< average <<std::endl;
}
catch(int &ex) { std::cerr <<"can't divide by zero"<<std::endl; }
catch(std::string &ex) { std::cerr << ex <<std::endl; }
catch(...) { std::cerr<<"Handling unknown exception"<<std::endl; }
```
Best practice is to throw an object, not a primitive type (like throw 0).  
For this, we have to use Exception classes (User-defined exceptions).  

```cpp
class DivideByZeroException{

};

float calculate_avg(int sum, int total){
    if(total == 0)
        throw DivideByZeroException();
    return static_cast<float>(sum) / total;
}

float average {};
try{
    average = calculate_avg(56, 100)
    std::cout<<"Average: "<< average <<std::endl;
}
catch(const DivideByZeroException &ex) { std::cerr <<"can't divide by zero"<<std::endl; }

```
We can derive our Exception class from the C++ STL exception class.  
The C++ STL exception class provive useful functions like the virtual function `what()` that
return a c-style string that describe the exception that occur.
```cpp
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

float average {};
try{
    average = calculate_avg(56, 100)
    std::cout<<"Average: "<< average <<std::endl;
}
catch(const DivideByZeroException &ex) {
    std::cerr <<ex.what()<<std::endl;
}

```

# Files I/O and Streams
__Some formatting:__  
- `#include <iomanip>`
- `std::cout << std::boolalpha;` All next `std::cout` will display true/false instead of 1/0 
- `std::cout << std::boolalpha;` Back to normal
- `std::cout << std::showpos;` Show the (+) or (-) sign of a number
- `std::cout<< std::setprecision(3) << std::fixed;` 3 digits after decimal point.

```cpp
#include <iomanip>

int a {255};
std::cout<< std::hex;
std::cout<< a <<std::endl;  // Display ff
```

```cpp
#include <iomanip>

int a {255};
std::cout<< std::showbase;
std::cout<< std::hex;
std::cout<< a <<std::endl;  // Display 0xff
```

```cpp
#include <iomanip>

int a {255};
std::cout<< std::showbase << std::uppercase;
std::cout<< std::hex;
std::cout<< a <<std::endl;  // Display 0XFF
```

`std::cout<< std::resetiosflags(std::ios::showpos)` : Reset a the manip passed in parameter to default.  
We can find more here : https://en.cppreference.com/w/cpp/io/manip

__Reading from text file:__  
- `#include <fstream>`
- declare an fstream or ifstream object
- connect the object to a file on the system (opens it)
- read data from the file via the stream
- close the stream

```cpp
std::ifstream myInfile {filepath}; // read-only object    
std::string line {};

if(!myInfile){
    std::cerr<<"File not found!" <<std::endl;
    return 1;
}

while(!myInfile.eof()){
    std::getline(myInfile, line);    // read a line
    std::cout << line << std::endl;
}
myInfile.close();
```

```cpp
myInfile >> word;  // read a word
std::cout << word << std::endl;
```

__Writing to a text file__   
By default C++ create the file if not exist. If it does, it will overwrite the content unless we specify.

```cpp
std::ofstream myFile_default {"../myfile_out.txt"}; // overwritting mode
std::ofstream myFile_append {"../myfile_out.txt", std::ios::app}; // append mode  

std::string date {"2013-10-14"};
std::string avis {"good"};
std::string cause {"no reason"};

if(!myFile_append){
    std::cerr<<"File not found!" <<std::endl;
    return 1;
}

for(size_t i=0; i<10; i++){

    myFile_append << std::setw(date.length()+5) << std::left << date 
                << std::setw(avis.length()+5) << avis
                << std::setw(cause.length()+5) << cause
                << std::endl;
}
myFile_append.close();
```
__Streams__: Very useful for data validation
```cpp
// placeholders
int num {};
float total {};
std::string name {};

std::string data_from_user {"Larry 70 100.57"};
```

store data from user into the input stream
```cpp
std::istringstream iss {data_from_user};
```

variables read from the stream. if this line runs, that meanvthe data from user is valid (match the variable types). Streams will allow to validate the data.
```cpp
iss >> name >> num >> total;

std::cout<< std::setw(10) << std::left << name
            << std::setw(10) << num
            << std::setw(10) << total
            << std::endl;
```

Output Stream useful for tranfering data.
```cpp
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
```

# STL
Sort container from the first element `vec.begin()` to the last+1 element. `v.end()` return an iterator at the location one after the lat element.
```cpp
#include <vector>
#include <algorithm>

std::vector<int> v {1, 5, 3};

std::sort(v.begin(), v.end()); //inplace

for(auto &elt: v)
    std::cout<< elt <<std::endl;
```

Reverse elements of a container
```cpp
std::reverse(v.begin(), v.end()); //inplace
```

Sum all the elements of a container
```cpp
#include <numeric>

int result_sum {};
int current_sum {0};

result_sum = std::accumulate(v.begin(), v.end(), current_sum);
```

Function template synthax
```cpp
template<typename T>
T max(T a, T b){
    return (a > b) ? a : b;
}
```

Class template synthax
```cpp

template<typename T>
class Item{

private:
    std::string name;
    T value;

public:
    Item(std::string name, T value)
        : name{name}, value{value} {}
    
    std::string get_name() const {
        return this->name;
    }
    
    T get_value() const {
        return this->value;
    }
};

```

Iterators:
- Synthax `container_type::iterator_type iterator_name` or `auto iterator_name`
- `iterator` normal it - works with `begin` and `end`
- `reverse_iterator` allow to iterate in reverse - works with `rbegin` and `rend`
- `const_iterator` - works with `cbegin` and `cend`
- `const_reverse_iterator` - works with `crbegin` and `crend`
```cpp
// reverse loop
std::vector<int>::reverse_iterator it2 = v.rbegin(); // or auto it2 = v.rbegin();

while (it2 != v.rend()) {
    std::cout<< *it2 <<std::endl;
    it2++;
}
```


```cpp

```

```cpp

```

```cpp

```

```cpp

```

# Best Practices
- Use cppcheck to check your code (act like a linter)

```shell 
sudo apt install cppcheck
cppcheck --enable=all ./*.cpp
```
- think twice when using for loop or range based for loop. The operation may already exist in the STL algorithm.
- use `for_each` with lambdas expression if need to apply operation on elements.

```cpp
std::for_each(v.begin(), v.end(), [](int &n) { n*=n; });
std::for_each(v.begin(), v.end(), [](const int &n) { std::cout << n <<std::endl;});
```

- Prefer range-based for loop or iterator over raw for loop
- Prefer enum class over traditional enum
- `std::transform` and `std::for_each` - replaces `map`

```cpp
std::transform(v.begin(), v.end(), std::back_inserter(v_square), [](int &n) { return n * n; });
```

- `std::copy_it` and `std::remove_if` - replaces `filter`

```cpp
std::copy_if(v.begin(), v.end(), std::back_inserter(v_even), [](const int &n) { return n % 2 == 0; });
```

- Reducing a collection to a scalar : Use `std::accumulate` - replace `reduce`
- `size_t` for unsigned integer improve code efficiency
- make `unique_ptr` your default pointer
- copy constructor, copy assignment operator, move constructor, move assignment operator. Do not create them, leave it to the compiler. If you create one, create all of them.
- `const` is your friend. Think of it by default. We can get performance boost, less bugs and it help the compiler.

```cpp
```

# C++ Unit tests
# CMake : Build C++ projects