#ifndef Complex_H
#define Complex_H

#include <iostream>
#include <cmath>
#include <sstream>

class Complex {
private:
    double real, imag;

public:
    Complex(double real_i = 0, double imag_i = 0);
    Complex(const Complex& other);
    ~Complex();

    double get_real() const;
    double get_imag() const;
    void set_real(double r);
    void set_imag(double i);

    double modulus() const;
    double argument() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    Complex& operator+=(const Complex& other);
    Complex conjugate() const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& cn);
    friend std::istream& operator>>(std::istream& is, Complex& cn);
};


#endif // Complex_H

