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

void MyParser::on_number_callback_default(const int number){

}

void MyParser::on_str_callback_default(const char* str){

}
void MyParser::start_callback_default(){

}
void MyParser::end_callback_default(){

}

MyParser::MyParser(){
    parse_start = &start_callback_default;
    parse_end = &end_callback_default;
    on_number_callback = &on_number_callback_default;
    on_str_callback = &on_str_callback_default;
}
void MyParser::parse(const char* text){
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