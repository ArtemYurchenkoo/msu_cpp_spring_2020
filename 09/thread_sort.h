#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <pthread.h>
#include <thread>
#include <algorithm>
#include <functional>

constexpr size_t MAX_MEMORY_AVAILABLE = 8 * 1024 * 1024;
constexpr size_t MAX_CHUNKS_MEMORY = 7 * 128 * 1024; // 7/8 of MAX_MEMORY_AVAILABLE, 1MB for all other stuff
constexpr size_t MAX_ELEMS = size_t(float(MAX_CHUNKS_MEMORY) / sizeof(uint64_t));
class ThreadSort{
private:
    std::vector<std::string> split(std::ifstream &input, uint64_t* buf){
        input.seekg(0, input.end);
        size_t len = input.tellg() / sizeof(uint64_t);
        input.seekg(0, input.beg);

        size_t n_chunks = 2 * std::ceil(float(len) / MAX_ELEMS);
        std::vector<std::string> names(n_chunks);
        for (size_t i = 0; i < n_chunks; ++i){
            names[i] = std::string("chunk") + std::to_string(i);
        }
        size_t chunk_id = 0;
        
        while (!input.eof()){
            input.read(reinterpret_cast<char*>(buf), MAX_ELEMS * sizeof(uint64_t));
            size_t read_count = input.gcount() / sizeof(uint64_t);

            std::thread t1([buf, read_count](){
                std::sort(buf, buf + read_count / 2);
            });
            std::thread t2([buf, read_count](){
                std::sort(buf + read_count / 2, buf + read_count);
            });
            t1.join();
            t2.join();

            std::ofstream chunk1(names[chunk_id], std::ios::binary);
            std::ofstream chunk2(names[chunk_id + 1], std::ios::binary);
            if (!(chunk1 && chunk2)){
                throw std::runtime_error("error with chunk");
            }
            chunk1.write(reinterpret_cast<const char*>(buf), sizeof(uint64_t) * read_count / 2);
            chunk2.write(reinterpret_cast<const char*>(buf + read_count / 2), sizeof(uint64_t) * read_count / 2);
            chunk1.close();
            chunk2.close();
            chunk_id += 2;
        }

        return names;
    } 

    void merge(std::vector<std::string>& names, uint64_t* buf){
        for (size_t i = 0; i < names.size() - 1; ++i){
            size_t pos = 0;
            uint64_t cur;
            std::ifstream chunk1(names[i], std::ios::binary);
            std::ifstream chunk2(names[i + 1], std::ios::binary);
            if (!(chunk1 && chunk2)){
                throw std::runtime_error("error with chunk");
            }

            chunk2.seekg(0, chunk2.end);
            size_t len = chunk2.tellg() / sizeof(uint64_t);
            chunk2.seekg(0, chunk2.beg);
            chunk2.read(reinterpret_cast<char*>(buf), len * sizeof(uint64_t));
            chunk2.close();
            chunk1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
            std::ofstream out(names[i + 1], std::ios::binary);
            if (!out){
                throw std::runtime_error("error with chunk");
            }

            while (pos < len && !chunk1.eof()){
                if (cur > buf[pos]){
                    out.write(reinterpret_cast<const char*>(&buf[pos]), sizeof(uint64_t));
                    ++pos;
                } else if (cur < buf[pos]){
                    out.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                    chunk1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
                } else {
                    out.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                    out.write(reinterpret_cast<const char*>(&buf[pos]), sizeof(uint64_t));
                    chunk1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
                    ++pos;
                }
            }

            if (pos >= len){
                while (!chunk1.eof()){
                    out.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                    chunk1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
                }
            } else if (chunk1.eof()){
                out.write(reinterpret_cast<const char*>(&buf[pos]), sizeof(uint64_t) * (len - pos));
            }
            chunk1.close();
            out.close();
        }
    } 

    void clear(std::vector<std::string>& names){
        for (size_t i = 0; i < names.size(); ++i){
            std::remove(names[i].c_str());
        }
    }

public:
    ThreadSort();
    void sort(const std::string& input, const std::string& output);
};