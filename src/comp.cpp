#include "comp.h"

Complex::Complex() : re(0), im(0) {
}

Complex::Complex(int re, int im) : re(re), im(im) {
}

bool Complex::operator<(const Complex& other) const {
    return re < other.re || (re == other.re && im < other.im);
}

bool Complex::operator>(const Complex& other) const {
    return re > other.re || (re == other.re && im > other.im);
}

bool Complex::operator==(const Complex& other) const {
    return re == other.re && im == other.im;
}

int Complex::GetRe() const {
    return re;
}

int Complex::GetIm() const {
    return im;
}

Complex Complex::Conj() const {
    return Complex(re, -im);
}

std::ostream& operator<<(std::ostream& os, const Complex& x) {
    os << x.GetRe() << " + i*" << x.GetIm();
    return os;
}
