#include "allocator.h"
//testing whether access control works fine
//alloc can be used once more only if reset was used
int main(){
    Allocator x;
    x.makeAllocator(1024);
    char* ptr1 = x.alloc(10);
    char* ptr2 = x.alloc(5);
    if (ptr2 == nullptr){
        std::cout << "Access works fine" << std::endl;
    } else {
        std::cout << "Access works badly" << std::endl;
    }
    return 0;
}