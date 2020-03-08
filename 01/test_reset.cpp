#include "allocator.h"
//testing whether reset sets allocator at starting state
int main(){
    Allocator x;
    x.makeAllocator(1024);
    char* ptr1 = x.alloc(5);
    x.reset();
    char* ptr2 = x.alloc(5);
    if (ptr1 == ptr2){
        std::cout << "Reset works fine" << std::endl;
    } else {
        std::cout << "Reset works badly" << std::endl;
    }
    return 0;
}