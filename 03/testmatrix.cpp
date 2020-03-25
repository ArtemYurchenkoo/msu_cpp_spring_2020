#include "matrix.h"
#include <cassert>

int main(){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix mmm(rows, cols);
    assert(mmm.getCols() == 3);
    assert(mmm.getRows() == 5);
    std::cout << "Getters work fine\n";
    mmm[1][2] = 5;
    double x = mmm[4][1];
    int y = mmm[1][2];
    assert(x == 0);
    assert(y == 5);
    std::cout << "[][] operator works fine\n";
    mmm *= 10;
    x = mmm[4][1];
    y = mmm[1][2];
    assert(x == 0);
    assert(y == 50);
    std::cout << "Multiplication works fine\n";
    Matrix m1(rows, cols);
    assert(m1 != mmm);
    m1[1][2] = 50;
    assert(m1 == mmm);
    std::cout << "operators == and != work fine\n";
    try{
        mmm[10][10] = 50;
    }
    catch(std::out_of_range){
        std::cout << "Range control works fine\n";
    }
    const Matrix matr(2, 1);
    mmm[1][2] = matr[1][0];
    assert(mmm[1][2] == 0); 
    try {} catch(...){}
    return 0;
}