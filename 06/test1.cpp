#include <iostream>
#include "format.h"
#include <cassert>

int main(){
    bool caught = false;

    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    
    try {
        text = format("{", 0);
    }
    catch (const std::runtime_error&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{0", 0);
    }
    catch (const std::runtime_error&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{}", 0);
    }
    catch (const std::runtime_error&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("}", 0);
    }
    catch (const std::runtime_error&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{{}}", 0);
    }
    catch (const std::runtime_error&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{1} {0}", 0);
    }
    catch (const std::runtime_error&){
        caught = true;
    }
    assert(caught);
    caught = false;


    text = format("{0}", 1);
    assert(text == "1");
    text = format("");
    assert(text == "");
    text = format("1");
    assert(text == "1");
    text = format("{0}{0}", "a");
    assert(text == "aa");
    std::cout << "Done\n";
    return 0;
}   