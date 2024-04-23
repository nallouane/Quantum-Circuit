#include "../h_files/Complex.h"

Complex::Complex(double real_i, double imag_i) : real(real_i), imag(imag_i) {}

Complex::Complex(const Complex& other) : real(other.real), imag(other.imag) {}

Complex::~Complex() {}

double Complex::get_real() const {
    return real;
}

double Complex::get_imag() const {
    return imag;
}

void Complex::set_real(double r) {
    real = r;
}

void Complex::set_imag(double i) {
    imag = i;
}

double Complex::modulus() const {
    return std::sqrt(std::pow(std::abs(real), 2) + std::pow(std::abs(imag), 2));
}

double Complex::argument() const {
    return std::atan2(imag, real);
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Complex((real * other.real + imag * other.imag) / denominator,
                   (imag * other.real - real * other.imag) / denominator);
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex Complex::conjugate() const {
    return Complex(real, -imag);
}

std::ostream& operator<<(std::ostream& os, const Complex& cn) {
    if (cn.imag == 0) {
        os << cn.real;
    } else if (cn.imag < 0) {
        os << cn.real << " - " << -cn.imag << "i";
    } else {
        os << cn.real << " + " << cn.imag << "i";
    }
    return os;
}


std::istream& operator>>(std::istream& is, Complex& cn) {
    char plus_or_minus_sign, i;
    double real, imag;
    is >> real >> plus_or_minus_sign >> imag >> i;

    if (i != 'i') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (plus_or_minus_sign == '-') {
        imag = -imag;
    }

    cn = Complex(real, imag);
    return is;
}

