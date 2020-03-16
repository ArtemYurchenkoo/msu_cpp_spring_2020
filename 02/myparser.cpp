#include "myparser.h"
#include <cctype>
#include <cstring>
#include <iostream>

void MyParser::register_on_number_callback(OnNumber callback){
    on_number_callback = callback;
}
void MyParser::register_on_str_callback(OnString callback){
    on_str_callback = callback;
    return;
}

void MyParser::parse(const char* text){
    std::cout << "Parsing starts\n";
    while ((*text) != '\0'){
        char* buf = new char[strlen(text) + 1];
        size_t i = 0;
        if (isdigit(*text)){
            while (!isspace(*text) && (*text != '\0')){
                buf[i++] = *text++;
            }
            buf[i] = '\0';
            on_number_callback(buf);
            delete []buf;
        } else if (isalpha(*text)){
            while (!isspace(*text) && (*text != '\0')){
                buf[i++] = *text++;
            }
            buf[i] = '\0';
            on_str_callback(buf);
            delete []buf;
        } else if (isspace(*text)){
            ++text;
        }
    }
    std::cout << "Parsing has ended\n";
}