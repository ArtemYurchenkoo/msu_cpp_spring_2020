#include "allocator.h"
//testing numerous alloc use
int main(){
    Allocator x;
    x.makeAllocator(1024);
    char* ptr = x.alloc(10);
    char* ptr2 = x.alloc(15);
    if ((ptr2 - ptr) == 15){
        std::cout << "Numerous alloc use works fine" << std::endl;
    } else {
        std::cout << "Numerous alloc use works badly" << std::endl;
        std::cout << (ptr2 - ptr) << std::endl;
    }
    return 0;
}