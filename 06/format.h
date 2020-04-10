#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

std::string to_string(int x) { return std::to_string(x); }
std::string to_string(unsigned int x) { return std::to_string(x); }
std::string to_string(long x) { return std::to_string(x); }
std::string to_string(unsigned long x) { return std::to_string(x); }
std::string to_string(long long x) { return std::to_string(x); }
std::string to_string(unsigned long long x) { return std::to_string(x); }
std::string to_string(float x) { return std::to_string(x); }
std::string to_string(double x) { return std::to_string(x); }
std::string to_string(long double x) { return std::to_string(x); }
std::string to_string(const char *x) { return std::string(x); }
std::string to_string(const std::string &x) { return x; }

template<class T> std::string to_string(const T &t){
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::string format_impl(const std::string &fmt, const std::vector<std::string> &strs)
{
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

template<class Arg, class ... Args> std::string format_impl(const std::string& fmt, std::vector<std::string>& strs, Arg&& arg, Args&& ... args)
{
    strs.push_back(to_string(arg));
    return format_impl(fmt, strs, args...);
}

std::string format(const std::string& fmt)
{
    return fmt;
}

template<class Arg, class ... Args> std::string format(const std::string& fmt, Arg&& arg, Args&& ... args)
{
    std::vector<std::string> strs;
    return format_impl(fmt, strs, arg, args...);
}