#include "myparser.h"
#include <iostream>

void onNumberFound(const int n){
    std::cout << n << '\n';
}

void onStrFound(const char* str){
    std::cout << str << '\n';
}

void start(){
    std::cout << "parsing starts\n";
}

void end(){
    std::cout << "parsing ends\n";
}

int main(){
    MyParser x;
    x.register_on_number_callback(onNumberFound);
    x.register_on_str_callback(onStrFound);
    x.register_on_end_callback(end);
    x.register_on_start_callback(start);
    x.parse("123 abc 4567");
    return 0;
}
