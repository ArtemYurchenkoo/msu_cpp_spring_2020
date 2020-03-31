#pragma once
#include <iostream>
#include <string>


enum class Error
{
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
    Error operator()(ArgsT&... args){
        return process(args...);
    }

private:

    template<class T>
    Error process(T& val){
        return Error::NoError;
    }
    
    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        process(val);
        return process(std::forward<Args>(args)...);
    }
};

template <>
Error Serializer::process<bool>(bool& val){
    if (val){
        o << "true" << Separator;
    } else {
        o << "false" << Separator;
    }
    return Error::NoError;
}

template <>
Error Serializer::process<uint64_t>(uint64_t& val){
    o << val << Separator;
    return Error::NoError;
}


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
        return process(std::forward<Args>(args)...);
    }
};

template<>
Error Deserializer::process<bool>(bool& val){
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

template<>
Error Deserializer::process<uint64_t>(uint64_t& val){
    std::string s;
    in >> s;
    if (s[0] >= '0' && s[0] <= '9'){
        val = atoi(s.data());
        return Error::NoError;
    }
    return Error::CorruptedArchive;
}

