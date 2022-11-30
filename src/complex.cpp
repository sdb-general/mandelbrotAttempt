#include <iostream>
#include "../include/complex.hpp"
#include <cmath>


const int gMaxIters = 500;


Complex::Complex(double aReal, double aImag) : 
  mReal{aReal}, mImag{aImag}
{}

Complex::Complex(const Complex& aOther) : 
  mReal{aOther.mReal}, mImag{aOther.mImag}
{std::cout << "copy called\n";}

Complex& Complex::operator= ( const Complex& aOther ){
  if (this == &aOther) return *this;
  mReal = aOther.mReal;
  mImag = aOther.mImag;
  return *this;
}

void Complex::display() const{
  std::cout << mReal << " + " << mImag << "j\n";
}

Complex Complex::operator* ( const Complex& aOther ){
  double lReal = mReal * aOther.mReal - mImag * aOther.mImag;
  //we can directly set mImag since we haven't modified mReal yet
  double lImag = mReal * aOther.mImag + mImag * aOther.mReal;
  // mReal = lReal;
  return Complex(lReal, lImag);
}

Complex Complex::operator- ( const Complex& aOther ){
  double lReal = mReal - aOther.mReal;
  double lImag = mImag - aOther.mImag;
  return Complex(lReal, lImag);
}


Complex& Complex::operator+= ( const Complex& aOther ){
  mReal += aOther.mReal;
  mImag += aOther.mImag;
  return *this;
}

double Complex::absolute() const{
  return mReal * mReal + mImag * mImag;
}



bool isMandelBrot(const Complex& aComplex){
  Complex lComplex{}, lLastComplex{};
  for (int lIter = 0; lIter < gMaxIters; lIter++){    
    if (lComplex.absolute() > 2) return false; // change this to abs val of local complex number
    lComplex = lLastComplex * lLastComplex; //starts at 0, this performs iterative step
    lComplex += aComplex;
    if ((lComplex - lLastComplex).absolute() < 1E-7) break;
    lLastComplex = lComplex;  
  }
  if (lComplex.absolute() < 2) return true;
  else return false;
}

