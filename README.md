### Stack and Heap Memory

The heap is a free store, we can put/Allocate as much things, objects, images as we want. But we need extra care : Free the head when we are done with it. So if we have an array but we do not know how big it is gonna be at runtime, it could be a good idea to allocate its memory dynamically on the heap (see section on dynamic memory allocation for more).

### Pointers
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

```
#### Dynamic memory Allocation
