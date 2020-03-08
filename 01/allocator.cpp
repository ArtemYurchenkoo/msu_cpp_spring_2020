#include "allocator.h"
Allocator::Allocator(){
    memory = nullptr;
    memory_start = nullptr;
    totalsize = 0;
    is_available = false;
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
    if (memory != NULL){
        memory_start = memory;
        totalsize = maxSize;
        is_available = true;
    }
    return;
}
char* Allocator::alloc(size_t size){
    if ((size <= 0) || (is_available == false)){
        return nullptr;
    }
    if (size <= totalsize){
        char* ptr = memory;
        is_available = false;
        return ptr;
    } else {
        return nullptr;
    }
}
void Allocator::reset(){
    memory = memory_start;
    if (memory != nullptr){
        is_available = true;
    }
    return;
}
