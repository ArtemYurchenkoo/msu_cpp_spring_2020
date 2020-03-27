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
    Error operator()(ArgsT... args)
    {
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
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:

    template<class T>
    Error read(T&& val){
        constexpr bool type_uint64_t = std::is_same<T, uint64_t(&)>::value;
        constexpr bool type_bool = std::is_same<T, bool(&)>::value;
        std::string s;
        in >> s;
        if (type_uint64_t && s[0] >= '0' && s[0] <= '9'){
            val = atoi(s.data());
            return Error::NoError;
        }
        if (type_bool){
            if (s == "true"){
                val = true;
                return Error::NoError;
            } else if (s == "false"){
                val = false;
                return Error::NoError;
            }
        }
        return Error::CorruptedArchive;
    }

    template<class T>
    Error process(T&& val){
        return read(std::forward<T>(val));
    }
    
    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        if (read(std::forward<T>(val)) != Error::NoError){
            return Error::CorruptedArchive;
        }
        return process(std::forward<Args>(args)...);
    }
}; 