#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "thread_sort.h"

void generate_file(const size_t count, const std::string& fn){
    std::ofstream out(fn, std::ios::binary);
    for (size_t i = 0; i < count; ++i){
        uint64_t num = rand();
        out.write(reinterpret_cast<char*>(&num), sizeof(uint64_t));
    }
    out.close();
}

int main(){
    size_t count = 1000 * 1000;
    generate_file(count, "test_input");
    ThreadSort("test_input", "test_output").sort();

    uint64_t* buf = new uint64_t [count];
    std::ifstream f("test_output", std::ios::binary);
    f.read(reinterpret_cast<char*>(buf), count * sizeof(uint64_t));
    if (std::is_sorted(buf, buf + count)){
        std::cout << "Successfully sorted" << std::endl;
    } else {
        std::cout << "Not sorted" << std::endl;
    }
    delete [] buf;
    f.close(); 
    return 0;
}