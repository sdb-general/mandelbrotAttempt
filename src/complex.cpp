#include <iostream>
#include "../include/complex.hpp"
#include <cmath>

#include <xmmintrin.h>

__m128d a;


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



bool isMandelBrot(const Complex& aComplex, const int aMaxIters){
  Complex lComplex{}, lLastComplex{};
  int lIter = 0;
  while ( (lIter < aMaxIters) and (lComplex.absolute() < 4))
  {    
    lComplex = lLastComplex * lLastComplex; //starts at 0, this performs iterative step
    lComplex += aComplex;
    // if ((lComplex - lLastComplex).absolute() < 1E-7) break;
    lLastComplex = lComplex;  
    lIter++;
  }
  return (lComplex.absolute() < 4);
}


bool isMandelBrot(const double& aReal, const double& aImag, const int aMaxIters)
{
  double zR(0), zI(0);
  double lTempReal;
  int lIter = 0;
  // auto isTooLarge = [&](double aZI, double aZR){ return (aZI * aZI + aZR * aZR) < 4 ;};
  while ( (lIter < aMaxIters) and ( (zR * zR + zI * zI) < 4 ) )
  // while ( (lIter < aMaxIters) and ( isTooLarge(zR, zI) ) )
  {
    lTempReal = zR;
    zR = zR * zR - zI * zI + aReal;
    zI = 2 * lTempReal * zI + aImag;

    lIter++;
  }

  // return isTooLarge(zR, zI);
  return ( (zR * zR + zI * zI) < 4 );
}

