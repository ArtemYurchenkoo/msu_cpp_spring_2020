#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

using std::to_string;

template<class T> std::string to_string(const T &t){
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::string format_impl(const std::string &fmt, const std::vector<std::string> &strs){
    std::string res;
    std::string buf;
    bool start_format = false;
    for (int i = 0; i < fmt.size(); ++i){
        char c = fmt[i];
        if (start_format){
            if (isdigit(c)){
                buf += c;
            } else {
                if (c != '}'){
                    throw std::runtime_error("");
                }
                size_t numb = 0;
                if (!buf.empty()){
                    numb = atoi(buf.c_str());
                } else {
                    throw std::runtime_error("");
                }
                if (numb < strs.size()){
                    res += strs[numb];
                } else {
                    throw std::runtime_error("");
                }
                buf.clear();
                start_format = false;
            }
        } else {
            if (c == '{') {
                start_format = true;
            } else  if (c == '}'){
                throw std::runtime_error("");
            } else {
                res += c;
            }
        }
    }
    if (start_format){
        throw std::runtime_error("");
    }
    return res;
}

std::string format(const std::string& fmt){
    return fmt;
}

template<class ... Args> std::string format(const std::string& fmt, Args&& ... args){
    std::vector<std::string> strs{to_string(std::forward<Args>(args))...};
    return format_impl(fmt, strs);
}