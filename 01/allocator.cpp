#include "allocator.h"
Allocator::Allocator(){
    memory = nullptr;
    memory_start = nullptr;
    totalsize = 0;
    cur_allocated = 0;
}
Allocator::~Allocator(){
    if (memory != nullptr){
        free(memory);
    }
}
void Allocator::makeAllocator(size_t maxSize){
    if (memory != nullptr){
        return;
    }
    memory = (char*)malloc(maxSize);
    if (memory != nullptr){
        memory_start = memory;
        totalsize = maxSize;
    }
    return;
}
char* Allocator::alloc(size_t size){
    if (size <= (totalsize - cur_allocated)){
        char* ptr = (memory + cur_allocated);
        cur_allocated += size;
        return ptr;
    } else {
        return nullptr;
    }
}
void Allocator::reset(){
    memory = memory_start;
    cur_allocated = 0;
    return;
}
