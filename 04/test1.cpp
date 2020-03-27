#include "serializer.h"
#include <iostream>
#include <cassert>
#include <sstream>

struct Data{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }
};

int main(){
    Data x { 1, true, 2 };
    std::stringstream s1;

    Serializer serializer(s1);
    serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(s1);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    return 0;
}
