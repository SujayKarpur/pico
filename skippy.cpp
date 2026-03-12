#include <vector>
#include <list> 
#include <limits> 
#include <random> 

#include "skippy.h"




//black box function that returns true 50% of the time, false 50% of the time 
bool coin_toss(void)
{
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    static std::bernoulli_distribution dist(0.5);
    
    return dist(gen); 
}




//simple, single-threaded skip list implementing an ordered set interface 

void skiplist::insert(int key)
{
    if (contains(key))
        return ; 

    int height = 0; 
    while (height<MAX_LEVEL && coin_toss())
        height++; 
    
    node *fresh = new node(key, height); 
    node *current = head; 
    for (int level=height; level >= 0; level--) 
    {
        while (current->forward[level] != nullptr && key > (current->forward[level])->key)
            current = current->forward[level]; 
        
        node *temp = current->forward[level]; 
        current->forward[level] = fresh; 
        fresh->forward[level] = temp; 
    }
}


bool skiplist::contains(int key)
{
    node *current = head; 
    for (int level=MAX_LEVEL; level >= 0; level--)
    {
        while (current->forward[level] != nullptr && (current->forward[level])->key)
            current = current->forward[level]; 

        if (current->forward[level] != nullptr && (current->forward[level])-> key == key)
            return true; 
    }
    return false; 
}


void skiplist::erase(int key)
{
    if (!contains(key))
        return ; 

    node *current = head; 
    for (int level=MAX_LEVEL; level >= 0; level--)
    {
        while (current->forward[level] != nullptr && (current->forward[level])->key)
            current = current->forward[level]; 

        if (current->forward[level] != nullptr && (current->forward[level])-> key == key)
        {
            node *temp = current->forward[level]; 
            current->forward[level] = temp->forward[level]; 

            if (level == 0)
                delete temp; 
        }
    }
}



//starting with a skip list implementing a set of ints contains() insert() and erase() 
//hten add stuff - generics, sugar etc 