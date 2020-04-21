#pragma once
#include <iostream>

template <class T>
class Allocator{
public:
    using value_type = T;
    using pointer = T*;
    using const_reference = const T&;

    Allocator() {};
    ~Allocator() {};

    pointer allocate(size_t count){
        if (count == 0){
            return nullptr;
        }
        pointer ptr = static_cast<pointer>(::operator new[](sizeof(value_type) * count));
        return ptr;
    }

    void deallocate(pointer ptr, size_t count){
        if (ptr == nullptr){
            return;
        }
        for(size_t i = 0; i < count; ++i){
            ptr[i].~value_type();
        }
        ::operator delete[](ptr);
    }
};

template <class T>
class Iterator{
    T* ptr_ = nullptr;
    bool reverse;

public:
    explicit Iterator(T* ptr, bool rev=false){
        ptr_ = ptr;
        reverse = rev;
    }

    bool operator==(const Iterator<T>& other) const{
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const{
        return !(*this == other);
    }

    Iterator& operator+=(size_t n){
        if (n >= 0){
            while (n--){
                reverse ? --ptr_ : ++ptr_;
            }
        } else {
            while (n++){
                reverse ? ++ptr_ : --ptr_;
            }
        }
        return ptr_;
    }

    Iterator& operator-=(size_t n){
        return *this->operator+=(-n);
    }

    Iterator operator+(size_t n) const{
        Iterator temp(ptr_);
        return temp += n;
    }

    Iterator operator-(size_t n) const{
        return *this->operator+(-n);
    }

    Iterator& operator++(){
        reverse ? --ptr_ : ++ptr_;
        return *this;
    }

    Iterator& operator--(){
        reverse ? ++ptr_ : --ptr_;
        return *this;
    }

    T& operator*() const{
        return *ptr_;
    }

    T& operator[](size_t n) const{
        return *(*this + n);
    }
};



template <class T, class Alloc = Allocator<T>>
class Vector{
    Alloc allocator;
    T* ptr;
    size_t capacity_;
    size_t size_;

public:
    using value_type = T;
    using reference = T&;
    using iterator = Iterator<T>;
    using const_reference = const T&;
	using allocator_type = Alloc;

    Vector(){
        allocator = Alloc();
        capacity_ = 4;
        ptr = allocator.allocate(capacity_);
        // for (size_t i = 0; i < capacity_; ++i){
            // ptr[i] = value_type();
        // }
        size_ = 0;
    }

    explicit Vector(size_t count){
        allocator = Alloc();
        capacity_ = 2 * count;
        ptr = allocator.allocate(capacity_);
        size_ = count;
        for (size_t i = 0; i < count; ++i){
            ptr[i] = value_type();
        }
    }

    Vector(size_t count, const_reference defaultValue){
        allocator = Alloc();
        capacity_ = 2 * count;
        ptr = allocator.allocate(capacity_);
        for (size_t i = 0; i < count; ++i){
            ptr[i] = defaultValue;
        }
    }

    ~Vector(){
        allocator.deallocate(ptr, size_);
    }

    iterator begin() noexcept{
        return iterator(ptr);
    }
    iterator rbegin() noexcept{
        return iterator(ptr + size_ - 1, true);
    }

    iterator end() noexcept{
        return iterator(ptr + size_);
    }

    iterator rend() noexcept{
        return iterator(ptr - 1, true);
    }

    bool empty() const noexcept{
        return size_ == 0;
    }

    void push_back(const_reference value){
        if (size_ == capacity_){
            resize(2 * capacity_);
        }
        ptr[size_++] = value;
    }

    void pop_back(){
        if (size_ > 0){
            ptr[--size_].~value_type();
        } else {
            throw std::out_of_range("pop_back in empty vector");
        }
    }

    reference operator[](size_t n){
        return ptr[n];
    }

    const_reference operator[](size_t n) const{
        return ptr[n];
    }
    reference at(size_t n){
        if (n > size_ || n < 0){
            throw std::out_of_range("");
        }
        return ptr[n];
    }

    const_reference at(size_t n) const{
        if (n > size_ || n < 0){
            throw std::out_of_range("");
        }
        return ptr[n];
    }

    void reserve(size_t count){
        if (count <= capacity_){
            return;
        }
        T* temp = allocator.allocate(count);
        for (size_t i = 0; i < size_; ++i){
            temp[i] = ptr[i];
        }
        allocator.deallocate(ptr, size_);
        capacity_ = count;
        ptr = temp;
    }   

    size_t capacity() const noexcept{
        return capacity_;
    }

    size_t size() const noexcept{
        return size_;
    }

    void resize(size_t newSize){
        if (size_ >= newSize){
            for (size_t i = newSize; i < size_; ++i){
                ptr[i].~value_type();
            }
        } else {
            if (capacity_ < newSize){
                reserve(2 * newSize);
            } 
            for (size_t i = size_; i < newSize; ++i){
                ptr[i] = value_type();
            }
        }
        size_ = newSize;
    }

    void resize(size_t newSize, const_reference defaultValue){
        if (size_ >= newSize){
            for (size_t i = newSize; i < size_; ++i){
                ptr[i].~value_type();
            }
        } else {
            if (capacity_ < newSize){
                reserve(2 * newSize);
            } 
            for (size_t i = size_; i < newSize; ++i){
                ptr[i] = defaultValue;
            }
        }
        size_ = newSize;
    }

    void clear() noexcept{
        for (size_t i = 0; i < size_; ++i){
            ptr[i].~value_type();
        }
        size_ = 0;
    }
};