#pragma once
#include <iostream>
class Allocator{
    char* memory;
    char* memory_start;
    size_t totalsize;
    size_t cur_allocated;
public:
    Allocator();
    ~Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
};