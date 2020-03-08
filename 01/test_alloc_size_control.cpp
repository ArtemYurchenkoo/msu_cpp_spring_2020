#include "allocator.h"
//testing whether alloc doesn't get out of Allocator's size
int main(){
    Allocator x;
    x.makeAllocator(1024);
    char* ptr = x.alloc(5000);
    if (ptr == nullptr){
        std::cout << "Size control works fine" << std::endl;
    } else {
        std::cout << "Size control works badly" << std::endl;
    }
    return 0;
}