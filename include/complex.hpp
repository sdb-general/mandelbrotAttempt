#pragma once

/*
ultimately 
*/

void includeFunction();

// struct Complex;

class MandelBrot{
public:
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

public:
  const Complex mStartComplex;
  Complex mVariableComplex;

  const int mIters = 100;

  bool mMandel = 0;


public:
  //default constructor
  MandelBrot(float aReal, float aImag);

  // MandelBrot& operator+ (const MandelBrot& aOther);
  // MandelBrot& operator+= (const MandelBrot& aOther);
  // MandelBrot& operator- (const MandelBrot& aOther);
  
  // MandelBrot& operator* (const MandelBrot& aOther);
  //add some others for other types

  float absolute() const;

  void display() const;

  void isMandelBrot();

};

