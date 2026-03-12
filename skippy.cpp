#include <iostream> 
#include <vector>
#include <list> 

//simple, single-threaded skip list implementing an ordered set interface 
class SkipList
{
    //what do i need 
    //vector of linkedlists ish 

    bool contains(int key); 
    void insert(int key); 
    void erase(int key); 

}; 


//starting with a skip list implementing a set of ints contains() insert() and erase() 
//hten add stuff - generics, sugar etc 