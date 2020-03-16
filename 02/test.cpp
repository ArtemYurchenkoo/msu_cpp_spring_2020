#include "myparser.h"
#include <iostream>

void onNumberFound(const char* n){
    std::cout << n << '\n';
}

void onStrFound(const char* str){
    std::cout << str << '\n';
}

int main(){
    MyParser x;
    x.register_on_number_callback(onNumberFound);
    x.register_on_str_callback(onStrFound);
    x.parse("123 abc 4567");
    return 0;
}
