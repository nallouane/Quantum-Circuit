#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include "Complex.h"

class Matrix {
private:
    int rows, cols;
    Complex* matrix_data;

public:
    Matrix(int nrows, int ncols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
    friend std::istream& operator>>(std::istream& is, Matrix& mat);

    Complex& operator()(int i, int j); //modifcation to take place
    Complex operator()(int i, int j) const; //promises not to modify the object.

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix transpose() const;
    Matrix submatrix(int row, int col) const;
    Complex determinant() const;
    int getRows() const;
    int getCols() const;

    // Add the static function declarations
    static Matrix identityMatrix(int size);
    static Matrix kroneckerProduct(const Matrix& a, const Matrix& b);
};


#endif // MATRIX_H
