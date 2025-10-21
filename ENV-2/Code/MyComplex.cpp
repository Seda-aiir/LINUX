#include "../myIncludes/MyComplex.h"
#include <cmath>
#include <iomanip>

MyComplex::MyComplex(double r, double i){
    re = r;
    im = i;
}

MyComplex MyComplex::operator+(const MyComplex& other) const {
    return MyComplex(re + other.re, im + other.im);
}

MyComplex MyComplex::operator-(const MyComplex& other) const {
    return MyComplex(re - other.re, im - other.im);
}

double MyComplex::modules() const {
    double sum = re * re + im * im;
    return std::sqrt(sum);
}

MyComplex MyComplex::multiply(double num) const {
    return MyComplex(re * num, im * num);
}


std::ostream& operator<<(std::ostream& os, const MyComplex& c) {
 os.unsetf(std::ios::floatfield);
    if (c.im >= 0)
        os << c.re << " + " << c.im << "i";
    else
        os << c.re << " - " << (-c.im) << "i";
    return os;
}

