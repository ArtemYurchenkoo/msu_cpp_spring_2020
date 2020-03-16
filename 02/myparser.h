#pragma once
using OnNumber = void (*)(const char* number);
using OnString = void (*)(const char* str);
class MyParser{
    OnNumber on_number_callback;
    OnString on_str_callback;
public:
    void parse(const char* text);
    void register_on_number_callback(OnNumber callback);
    void register_on_str_callback(OnString callback);
};