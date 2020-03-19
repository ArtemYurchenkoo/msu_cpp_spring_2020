#pragma once
using OnNumber = void (*)(const int number);
using OnString = void (*)(const char* str);
using StartEnd = void (*)();
class MyParser{
    OnNumber on_number_callback;
    OnString on_str_callback;
    StartEnd parse_end;
    StartEnd parse_start;
    void static on_number_callback_default(const int number);
    void static on_str_callback_default(const char* str);
    void static start_callback_default();
    void static end_callback_default();
public:
    MyParser();
    void parse(const char* text);
    void register_on_number_callback(OnNumber callback);
    void register_on_str_callback(OnString callback);
    void register_on_start_callback(StartEnd callback);
    void register_on_end_callback(StartEnd callback);
};