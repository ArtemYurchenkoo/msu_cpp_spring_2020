#include "bigint.h"

BigInt::BigInt(){
    initByZero();
}

BigInt::BigInt(const long long& value){
    if (value < 0){
        this->initByString(std::to_string(-1 * value));
        sign = true;
    } else {
        this->initByString(std::to_string(value));
        sign = false;
    }
}

BigInt::~BigInt(){
    delete [] data;
}

BigInt::BigInt(const BigInt& other){
    length = other.length;
    sign = other.sign;
    data = new char[length];
    for (size_t i = 0; i < length; ++i){
        data[i] = other.data[i];
    }
}

BigInt::BigInt(const std::string& str){
    initByString(str);
}

void BigInt::initByZero(){
    length = 1;
    data = new char[length];
    data[0] = 0;
    sign = false;
}

void BigInt::initByString(const std::string& str){
    size_t start = str.find_first_not_of("0-");
    if (start != std::string::npos){
        length = str.size() - start;
        data = new char[length];
        std::string::const_iterator p = str.begin();
        for (size_t i = 0; i < start; ++i){
            ++p;
        }
        size_t pos = length - 1;
        while (p != str.end()){
            data[pos] = *p - '0';
            ++p;
            --pos;
        }
    } else {
        initByZero();
    }
    if (str[0] == '-'){
            sign = true;
    }
    return;
}

BigInt& BigInt::operator=(const BigInt& other){
    if (this == &other){
        return *this;
    }
    char* new_data = new char[other.findLast() + 1];
    for (size_t i = 0; i <= other.findLast(); ++i){
        new_data[i] = other.data[i];
    }
    delete [] data;
    length = other.findLast() + 1;
    sign = other.sign;
    data = new_data;
    return *this;
}

bool BigInt::getSign() const{
    return sign;
}

bool BigInt::resize(size_t size){
    char* new_data = new char[size];
    for(size_t i = 0; i < length; ++i){
        new_data[i] = data[i];
    }
    for(size_t i = length; i < size; ++i){
        new_data[i] = 0;
    }
    delete[] data;
    data = new_data;
    length = size;
}

BigInt BigInt::add(const BigInt& other) const{
    //this function is only called when
    //both values are >= 0
    //first operand's length is > than second's
    BigInt result = *this;
    for (size_t i = 0; i < other.length; ++i){
        result.data[i] += other.data[i];
        char overflow = 0;
        if (result.data[i] > 9){
            overflow = 1;
            result.data[i] -= 10;
        }
        if (overflow != 0){
            if ((i + 1) == result.length){
                result.resize(result.length + 10);
            }
            ++result.data[i + 1];
        }
    }
    for (size_t i = other.length; i < length; ++i){
        char overflow = 0;
        if (result.data[i] > 9){
            overflow = 1;
            result.data[i] -= 10;
        }
        if (overflow != 0){
            if ((i + 1) == result.length){
                result.resize(result.length + 1);
            }
            ++result.data[i + 1];
        }
    }
    result.length = result.findLast() + 1;
    return result;
}

BigInt BigInt::substract(const BigInt& other) const{
    //this function is only called when
    //first operand is greater than second, both >= 0
    if (this == &other){
        return BigInt();
    }
    BigInt result = *this;
    BigInt sub = other;
    sub.resize(result.length);
    bool over = false;
    for(size_t i = 0; i < result.length; ++i){
        result.data[i] = result.data[i] - sub.data[i] - over;
        over = false;
        if (result.data[i] < 0){
            result.data[i] += 10;
            over = true;
        }
    }
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const{
    //a - b = a + (-b)
    return this->operator+(other.operator-());
}

BigInt BigInt::operator+(const BigInt& other) const{
        //a + b = b + a, so the first operand will be 
        //the one with greater length
        if ((sign && other.sign) || (!sign && !other.sign)){
        if (length > other.length){
            return add(other);
        } else {
            return other.add(*this);
        }
    }
    if (sign && !other.sign){
        if (*this < other.operator-()){
            BigInt temp = substract(other);
            temp.sign = sign;
            return temp;
        } else {
            BigInt temp = other.substract(*this);
            temp.sign = !sign;
            return temp;
        }
    }
    if (!sign && other.sign){
        if (*this > other.operator-()){
            BigInt temp = substract(other);
            temp.sign = sign;
            return temp;
        } else {
            BigInt temp = other.substract(*this);
            temp.sign = !sign;
            return temp;
        }
    }
}

BigInt& BigInt::operator+=(const BigInt& other){
    *this = this->operator+(other);
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other){
    *this = this->operator-(other);
    return *this;
}

BigInt& BigInt::operator-(){
    this->sign = !this->sign;
    return *this;
}

BigInt BigInt::operator-() const{
    BigInt temp(*this);
    temp.sign  = !temp.sign;
    return temp;
}

bool BigInt::operator<(const BigInt& other) const{
    if (this == &other){
        return false;
    }
    if (sign && other.sign){
        return this->operator-().operator>(other.operator-());
    }
    if (sign && !other.sign){
        return true;
    }
    if (!sign && other.sign){
        return false;
    }
    if (findLast() < other.findLast()){
        return true;
    } else if (findLast() > other.findLast()){
        return false;
    } else {
        for (size_t i = findLast() + 1; i > 0; --i){
            if (data[i - 1] < other.data[i - 1]){
                return true;
            }
            if (data[i - 1] > other.data[i - 1]){
                return false;
            }
        }
        return false;
    }
}

bool BigInt::operator>(const BigInt& other) const{
    if (this == &other){
        return false;
    }
    if (sign && other.sign){
        return this->operator-().operator<(other.operator-());
    }
    if (sign && !other.sign){
        return false;
    }
    if (!sign && other.sign){
        return true;
    }
    if (findLast() > other.findLast()){
        return true;
    } else if (findLast() < other.findLast()){
        return false;
    } else {
        for (size_t i = findLast() + 1; i > 0; --i){
            if (data[i - 1] > other.data[i - 1]){
                return true;
            }
            if (data[i - 1] < other.data[i - 1]){
                return false;
            }
        }
        return false;
    }
}

bool BigInt::operator<=(const BigInt& other) const{
    return !this->operator>(other);
}

bool BigInt::operator>=(const BigInt& other) const{
    return !this->operator<(other);
}

bool BigInt::operator==(const BigInt& other) const{
    if (this == &other){
        return true;
    }
    size_t len = findLast();
    size_t other_len = other.findLast();
    if (len != other_len){
        return false;
    }
    if ((len == other_len) && (len == 0) && (data[0] == other.data[0]) && (data[0] == 0)){
        return true;
    }
    if (sign != other.sign){
        return false;
    }
    for (size_t i = 0; i < findLast() + 1; ++i){
        if (data[i] != other.data[i]){
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const{
    return !this->operator==(other);
}

size_t BigInt::findLast() const{
    for (size_t i = length; i > 0; --i){
        if (data[i - 1] > 0){
            return i - 1;
        }
    }
    return 0;
}

std::string BigInt::toString() const{
    std::string s = "";
    if (sign){
        s += '-';
    }
    for (size_t i = findLast() + 1; i > 0; --i){
        s += std::to_string(int(data[i - 1]));
    }
    return s;
}

std::ostream& operator<<(std::ostream& stream, const BigInt& big){
    size_t len = big.findLast();
    if ((len == 0) && (big.data[0] == 0)){
        stream << 0;
        return stream;
    }
    if (big.sign){
        stream << '-';
    }
    for (size_t i = len + 1; i > 0; --i){
        stream << int(big.data[i - 1]);
    }
    return stream;
}
