#pragma once
#include <iostream>
#include <string.h>

class BigInt{
public:
    size_t length;
    char* data;
    bool sign = false;

public:
    BigInt();
    BigInt(const std::string&);
    BigInt(const BigInt&);
    BigInt(const long long&);
    ~BigInt();
    BigInt& operator=(const BigInt&);
    bool getSign() const;
    BigInt operator-() const;
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);

    bool operator<(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

private:
    bool resize(size_t size);
    std::string toString() const;
    BigInt add(const BigInt&) const;
    BigInt substract(const BigInt&) const;
    size_t findLast() const;
    void initByString(const std::string&);
    void initByZero();
};