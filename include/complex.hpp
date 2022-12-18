#pragma once

struct Complex{
    double mReal;
    double mImag;

    Complex operator* (const Complex& aOther);
    Complex& operator+= (const Complex& aOther);
    Complex operator- (const Complex& aOther);
    //modify the above to return a newly constructed object

    // need a constrcutor that defaults to 0
    Complex(double aReal, double aImag);
    Complex() = default;


    Complex(const Complex& aOther);
    Complex& operator= (const Complex& aOther);

    void display() const;

    double absolute() const;
};


bool isMandelBrot(const Complex& aComplex, const int aMaxIters);