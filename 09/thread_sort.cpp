#include "thread_sort.h"
#include <fstream>
#include <iostream>

ThreadSort::ThreadSort(){};

void ThreadSort::sort(const std::string& inp, const std::string& out){
    std::ifstream input(inp, std::ios::binary);
    if (!input){
        throw std::runtime_error("input file error");
    }
    uint64_t* buf = new uint64_t [MAX_CHUNKS_MEMORY];
    try{
        std::vector<std::string> names = split(input, buf);
        merge(names, buf);
        std::rename(names.back().c_str(), out.c_str());
        names.pop_back();
        clear(names);
    } catch (...){
        delete [] buf;
        input.close();
        throw;
    }
    delete [] buf;
    input.close();
}

