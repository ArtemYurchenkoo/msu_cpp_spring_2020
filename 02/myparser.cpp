#include "myparser.h"
#include <cctype>
#include <cstring>
#include <iostream>

void MyParser::register_on_number_callback(OnNumber callback){
    on_number_callback = callback;
}
void MyParser::register_on_str_callback(OnString callback){
    on_str_callback = callback;
}

void MyParser::register_on_start_callback(StartEnd callback){
    parse_start = callback;
}

void MyParser::register_on_end_callback(StartEnd callback){
    parse_end = callback;
}

MyParser::MyParser(){
    parse_start = nullptr;
    parse_end = nullptr;
    on_number_callback = nullptr;
    on_str_callback = nullptr;
}
void MyParser::parse(const char* text){
    if ((parse_end == nullptr) || (parse_start == nullptr) || 
        (on_str_callback == nullptr) || (on_number_callback == nullptr)){
            std::cerr << "Uninitialized callback";
            return;
        }
    parse_start();
    while ((*text) != '\0'){
        std::string buf;
        if (isdigit(*text)){
            while (!isspace(*text) && (*text != '\0')){
                buf.push_back(*text++);
            }
            buf.push_back('\0');
            on_number_callback(atoi(buf.c_str()));
        } else if (isalpha(*text)){
            while (!isspace(*text) && (*text != '\0')){
                buf.push_back(*text++);
            }
            buf.push_back('\0');
            on_str_callback(buf.c_str());
        } else if (isspace(*text)){
            ++text;
        }
    }
    parse_end();
    return;   
}