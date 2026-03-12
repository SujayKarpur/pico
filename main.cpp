#include "skippy.h"
#include <iostream> 


int main(void)
{
    std::cout << "hello world\n"; 

    skiplist s; 
    s.insert(3); 
    std::cout << s.contains(3) << "\n"; 

    return 0; 
}

// v vague roadmap
// single-threaded, locked, and lock-free skip lists //wait free?
// simple memtable 
// 3 bench suites -- mixed, read-heavy, and write-heavy 
// maybe map/umap too idk 

//usage could be like
    // ./pico 
    // ./pico -bench 