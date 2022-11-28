#pragma once

struct Complex{
    float mReal;
    float mImag;

    Complex operator* (const Complex& aOther);
    Complex& operator+= (const Complex& aOther);
    Complex operator- (const Complex& aOther);
    //modify the above to return a newly constructed object

    // need a constrcutor that defaults to 0
    Complex(float aReal, float aImag);


    Complex(const Complex& aOther);
    Complex& operator= (const Complex& aOther);

    void display() const;

    float absolute() const;
  };


bool isMandelBrot(const Complex& aComplex);