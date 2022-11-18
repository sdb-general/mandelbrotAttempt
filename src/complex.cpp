#include <iostream>
#include "../include/complex.hpp"
#include <cmath>

// void includeFunction(){
//   std::cout << "printing inside included function\n";
// }

MandelBrot::Complex::Complex(float aReal = 0, float aImag = 0) : 
  mReal{aReal}, mImag{aImag}
{}

MandelBrot::Complex::Complex(const Complex& aOther) : 
  mReal{aOther.mReal}, mImag{aOther.mImag}
{std::cout << "copy called\n";}

MandelBrot::Complex& MandelBrot::Complex::operator= ( const MandelBrot::Complex& aOther ){
  if (this == &aOther) return *this;
  mReal = aOther.mReal;
  mImag = aOther.mImag;
  return *this;
}

void MandelBrot::Complex::display() const{
  std::cout << mReal << " + " << mImag << "j\n";
}

MandelBrot::Complex MandelBrot::Complex::operator* ( const MandelBrot::Complex& aOther ){
  float lReal = mReal * aOther.mReal - mImag * aOther.mImag;
  //we can directly set mImag since we haven't modified mReal yet
  float lImag = mReal * aOther.mImag + mImag * aOther.mReal;
  // mReal = lReal;
  return Complex(lReal, lImag);
}

MandelBrot::Complex MandelBrot::Complex::operator- ( const MandelBrot::Complex& aOther ){
  float lReal = mReal - aOther.mReal;
  float lImag = mImag - aOther.mImag;
  return Complex(lReal, lImag);
}


MandelBrot::Complex& MandelBrot::Complex::operator+= ( const MandelBrot::Complex& aOther ){
  mReal += aOther.mReal;
  mImag += aOther.mImag;
  return *this;
}

float MandelBrot::Complex::absolute() const{
  return mReal * mReal + mImag * mImag;
}

MandelBrot::MandelBrot(float aReal, float aImag) : 
  mStartComplex{aReal, aImag}, mVariableComplex{}
{}

void MandelBrot::display() const{
  mVariableComplex.display();
}

float MandelBrot::absolute() const{
  return mVariableComplex.absolute();
}

void MandelBrot::isMandelBrot(){
  //add some way to quit if there's no real changes detected
  Complex lComplex{};
  for (int lIter = 0; lIter < mIters; lIter++){    
    if (absolute() > 2) return;
    lComplex = mVariableComplex * mVariableComplex;
    lComplex += mStartComplex;
    if ((lComplex - mVariableComplex).absolute() < 1E-7) break;
    mVariableComplex = lComplex;
    std::cout << "made it to round " << lIter << "\n";
  }
  if (absolute() < 2) mMandel = 1;
  
}

