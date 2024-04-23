#include "../h_files/Matrix.h"

Matrix::Matrix(int nrows, int ncols) :
    rows(nrows), cols(ncols), matrix_data(new Complex[nrows * ncols]) {}

Matrix::Matrix(const Matrix& other) :
    rows(other.rows), cols(other.cols), matrix_data(new Complex[other.rows * other.cols]) {
    for (int i = 0; i < rows * cols; i++) {
        matrix_data[i] = other.matrix_data[i];
    }
}

Matrix::Matrix(Matrix&& other) :
    rows(other.rows), cols(other.cols), matrix_data(other.matrix_data){
    other.matrix_data = nullptr;
}

Matrix::~Matrix() {
    delete[] matrix_data;
}

Matrix& Matrix::operator=(Matrix&& other) {
    if (this != &other) {
        delete[] matrix_data;
        rows = other.rows;
        cols = other.cols;
        matrix_data = other.matrix_data;
        other.matrix_data = nullptr;
    }
    return *this;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] matrix_data;
        rows = other.rows;
        cols = other.cols;
        matrix_data = new Complex[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            matrix_data[i] = other.matrix_data[i];
        }
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            os << std::setw(8) << std::setprecision(3) << mat(i + 1, j + 1);
        }
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& mat) {
    for (int i = 0; i < mat.rows * mat.cols; i++) {
        is >> mat.matrix_data[i];
    }
    return is;
}

Complex& Matrix::operator()(int i, int j) {
    return matrix_data[(i - 1) * cols + (j - 1)];
}

Complex Matrix::operator()(int i, int j) const {
    return matrix_data[(i - 1) * cols + (j - 1)];
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rows, cols);
    if (rows == other.rows && cols == other.cols) {
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows, cols);
    if (rows == other.rows && cols == other.cols) {
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                result(i, j) = (*this)(i, j) - other(i, j);
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Invalid matrix dimensions for multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= other.cols; j++) {
            Complex sum(0, 0); // Changed type from double to Complex
            for (int k = 1; k <= cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}


Matrix Matrix::identityMatrix(int size) {
    Matrix result(size, size);
    for (int i = 1; i <= size; i++) {
        result(i, i) = Complex(1, 0);
    }
    return result;
}

Matrix Matrix::kroneckerProduct(const Matrix& a, const Matrix& b) {
    int rows = a.getRows() * b.getRows();
    int cols = a.getCols() * b.getCols();
    Matrix result(rows, cols);

    for (int i = 1; i <= a.getRows(); i++) {
        for (int j = 1; j <= a.getCols(); j++) {
            for (int k = 1; k <= b.getRows(); k++) {
                for (int l = 1; l <= b.getCols(); l++) {
                    result((i - 1) * b.getRows() + k, (j - 1) * b.getCols() + l) = a(i, j) * b(k, l);
                }
            }
        }
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::submatrix(int row, int col) const {
    Matrix submatrix(rows - 1, cols - 1);
    for (int i = 1; i <= rows; i++) {
        if (i == row) continue;
        for (int j = 1; j <= cols; j++) {
            if (j == col) continue;
            submatrix(i < row ? i : i - 1, j < col ? j : j - 1) = (*this)(i, j);
        }
    }
    return submatrix;
}

Complex Matrix::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Invalid matrix dimensions for determinant");
    }

    if (rows == 1) {
        return (*this)(1, 1);
    }

    Complex det(0.0, 0.0);
    for (int j = 1; j <= cols; j++) {
        Complex multiplier(j % 2 == 1 ? 1.0 : -1.0, 0.0);
        det += multiplier * (*this)(1, j) * submatrix(1, j).determinant();
    }
    return det;
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}






