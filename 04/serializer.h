#pragma once
#include <iostream>
#include <string>


enum class Error{
    NoError,
    CorruptedArchive
};

class Serializer{
    static constexpr char Separator = ' ';
    std::ostream& o;

public:

    explicit Serializer(std::ostream& out): o(out){}

    template <class T>
    Error save(T& object){
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) const{
        return process(args...);
    }

private:

    template<class T>
    Error process(T& val) const{
        return Error::NoError;
    }
    
    template <class T, class... Args>
    Error process(T&& val, Args&&... args) const{
        process(val);
        return process(args...);
    }

    Error process(uint64_t& val) const{
        o << val << Separator;
        return Error::NoError;
    }

    Error process(bool& val) const{
        if (val){
            o << "true" << Separator;
        } else {
            o << "false" << Separator;
        }
        return Error::NoError;
    }
};

class Deserializer{
    std::istream& in;

public:

    explicit Deserializer(std::istream& instr): in(instr){
    }

    template <class T>
    Error load(T& object){
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args){
        return process(args...);
    }

private:

    template<class T>
    Error process(T& val){
        return Error::CorruptedArchive;
    }
    
    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        if (process(val) != Error::NoError){
            return Error::CorruptedArchive;
        }
        return process(args...);
    }

    Error process(bool& val){
        std::string s;
        in >> s;
        if (s == "true"){
            val = true;
            return Error::NoError;
        } else if (s == "false"){
            val = false;
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

    Error process(uint64_t& val){
        std::string s;
        in >> s;
        if (checkInt(s)){
            val = atoi(s.data());
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

    bool checkInt(const std::string& s) const{
        std::string::const_iterator i = s.begin();
        while (i != s.end()){
            if (!(isdigit(*i++))){
                return false;
            }
        }
        return true;
    }
};