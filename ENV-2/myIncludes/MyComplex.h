#ifndef MY_COMPLEX_H
#define MY_COMPLEX_H

#include <iostream>

class MyComplex {
private:
    double re, im;

public:
    MyComplex(double r = 0.0, double i = 0.0);

    MyComplex operator+(const MyComplex& other) const;
    MyComplex operator-(const MyComplex& other) const;
    MyComplex multiply(double num) const;

    double modules() const;
    
    double getReal() const {
	 return re;
    }
    double getImag() const { 
	return im;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyComplex& c);
};

#endif
