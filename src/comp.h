#pragma once

#include <iostream>

class Complex {
public:
    Complex();

    Complex(int re, int im);

    bool operator<(const Complex& other) const;

    bool operator>(const Complex& other) const;

    bool operator==(const Complex& other) const;

    int GetRe() const;

    int GetIm() const;

    Complex Conj() const;

private:
    int re, im;
};

std::ostream& operator<<(std::ostream& os, const Complex& x);
