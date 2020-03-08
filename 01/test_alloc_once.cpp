#include "allocator.h"
//testing whether alloc returns not nullptr
int main(){
    Allocator x;
    x.makeAllocator(1024);
    char* ptr = x.alloc(5);
    if (ptr != nullptr){
        std::cout << "Alloc works fine" << std::endl;
    } else {
        std::cout << "Alloc works badly" << std::endl;
    }
    return 0;
}