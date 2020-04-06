#include <iostream>
#include "bigint.h"
#include <sstream>
#include <cassert>


std::string toString(const BigInt& value)
{
    std::stringstream buf;
    buf << value;
    return buf.str();
}

void check(const BigInt& actual, const char* expected){
    assert(toString(actual) == expected);
}

int main(){
    BigInt x = 55;
    check(x, "55");
    BigInt y = x;
    check(y, "55");
    BigInt z;
    check(z, "0");
    check(BigInt(-10), "-10");
    assert(x == x);
    assert(x == y);
    assert(x != z);
    assert(x < 100);
    assert(x > 50);
    assert(x <= 55);
    assert(x <= x);
    assert(x >= x);
    assert(!(x < x));
    assert(BigInt(0) == -BigInt(0));
    assert(-x < 0);
    check(BigInt(10) - BigInt(10), "0");
    check(BigInt(-10) - BigInt(10), "-20");
    check(BigInt(10) - BigInt(-10), "20");
    check(BigInt(-10) - BigInt(-10), "0");
    std::cout << "\nDone\n";
    return 0;
}