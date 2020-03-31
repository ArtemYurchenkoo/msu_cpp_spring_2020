#pragma once
#include <iostream>
#include <exception>

class Matrix{
    class Row{
        int* row;
        size_t cols;
    public:
        Row(size_t m);
        Row();
        ~Row();
        bool operator==(const Row & other) const;
        bool operator!=(const Row & other) const;
        int & operator[](size_t c);
        const int & operator[](size_t c) const;
        Row & operator*=(const int value);
        void operator=(const Row & r);
    };
    Row* items;
    size_t n_rows;
    size_t n_cols;
public:
    Matrix(size_t n, size_t m);
    ~Matrix();
    size_t getRows() const;
    size_t getCols() const;
    Row & operator[](size_t r);
    const Row & operator[](size_t r) const;
    bool operator==(const Matrix & other) const;
    bool operator!=(const Matrix & other) const;
    Matrix & operator*=(const int value);
};