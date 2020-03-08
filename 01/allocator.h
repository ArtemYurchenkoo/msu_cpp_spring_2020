#pragma once
#include <iostream>
class Allocator{
    char* memory;
    char* memory_start;
    unsigned long long totalsize;
    bool is_available;
public:
    Allocator();
    ~Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
};