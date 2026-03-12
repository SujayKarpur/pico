#pragma once 

#include <vector>
#include <list> 
#include <limits> 
#include <random> 


const int INF = std::numeric_limits<int>::max(); 
const int NUM_LEVELS = 64;
const int MAX_LEVEL = NUM_LEVELS - 1; 

struct node 
{
    int key; 
    int height; 
    node *forward[NUM_LEVELS]; 

    node(int v, int h=0): key(v)
    {
        height = h; 
        for (int i=0; i<NUM_LEVELS; i++)
            forward[i] = nullptr; 
    }
};


class skiplist
{
    private: 
        node *head = new node(-INF, MAX_LEVEL); 

    public: 
        void insert(int key); 
        bool contains(int key); 
        void erase(int key); 
}; 