#include <vector>
#include <list> 
#include <limits> 
#include <random> 

const int INF = std::numeric_limits<int>::max(); 
const int NUM_LEVELS = 64;
const int MAX_LEVEL = NUM_LEVELS - 1; 


//black box function that returns true 50% of the time, false 50% of the time 
bool coin_toss(void)
{
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    static std::bernoulli_distribution dist(0.5);
    
    return dist(gen); 
}


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


//simple, single-threaded skip list implementing an ordered set interface 
class skiplist
{
    //what do i need 
    //vector of linkedlists ish 
    private: 
        node *head = new node(-INF, MAX_LEVEL);

    public: 

    void insert(int key)
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

    bool contains(int key)
    {
        node *current = head; 
        for (int level=MAX_LEVEL; level >= 0; level--)
        {
            while (current->forward[level] != nullptr && (current->forward[level])->key)
                current = current->forward[level]; 

            if (current->forward[level] != nullptr && (current->forward[level])-> key == key)
                return true; 
        }
    }


    void erase(int key)
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

}; 


//starting with a skip list implementing a set of ints contains() insert() and erase() 
//hten add stuff - generics, sugar etc 