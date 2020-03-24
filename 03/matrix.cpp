#include <iostream>
#include <cassert>
#include <exception>
#include <new>
#include "matrix.h"

Matrix::Row::Row(size_t m){
    row = new int[m];
    cols = m;
    for (size_t i = 0; i < m; ++i){
        row[i] = 0;
    }
}
        
Matrix::Row::Row(){
    row = nullptr;
}

Matrix::Row::~Row(){
}

bool Matrix::Row::operator==(const Row & other) const{
    if (cols != other.cols){
        return false;
    }
    for (size_t i = 0; i < cols; ++i){
        if (row[i] != other.row[i]){
            return false;
        }
    }
    return true;
}

bool Matrix::Row::operator!=(const Row & other) const{
    return !(*this == other);
}

int & Matrix::Row::operator[](size_t c){
    if (c - 1 > cols){
        throw std::out_of_range("");
    }
    return row[c -1];
}

const int & Matrix::Row::operator[](size_t c) const{
    if (c - 1 > cols){
        throw std::out_of_range("");
    }
    return row[c -1];
}

Matrix::Row & Matrix::Row::operator*=(const int value){
    for (size_t i = 0; i < cols; ++i){
        row[i] *= value;
    }
    return *this;
} 

void Matrix::Row::operator=(const Row & r){
    delete [] row;
    cols = r.cols;
    row = new int [cols];
    for (size_t i = 0; i < cols; ++i){
        row[i] = r.row[i];
    }
}

Matrix::Matrix(size_t n, size_t m){
    items = new Row[n];
    for (size_t i = 0; i < n; ++i){
        Row* ptr = new (items + i) Row(m);
    }
    n_cols = m;
    n_rows = n;
}

Matrix::~Matrix(){
    for(size_t i = 0; i < n_rows; ++i){
        delete [] items[i].row;
        items[i].~Row();
    }
    delete [] items;
}

size_t Matrix::getRows() const{
    return n_rows;
}

size_t Matrix::getCols() const{
    return n_cols;
}

Matrix::Row & Matrix::operator[](size_t r){
    return items[r - 1];
}

const Matrix::Row & Matrix::operator[](size_t r) const{
    return items[r - 1];
}

bool Matrix::operator==(const Matrix & other) const{
    if ((n_cols != other.n_cols) || (n_rows != other.n_rows)){
        throw std::out_of_range("");
    }
    for (size_t i = 0; i < n_rows; ++i){
        if (items[i] !=  other.items[i]){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix & other) const{
    return !(*this == other);
}

Matrix & Matrix::operator*=(const int value){
    for(size_t i = 0; i < n_rows; ++i){
        items[i] *= value;
    }
    return *this; 
}