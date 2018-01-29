#include<iostream>
#include"Complex.hpp"


Complex::Complex( double real, double imaginary ) {
 setComplexNumber( real, imaginary );
 } // end Complex constructor
Complex::Complex(){
  setComplexNumber(0, 0);
}
Complex Complex::add( const Complex &right ) {
  Complex c;
  c.setComplexNumber(realPart + right.realPart, imaginaryPart + right.imaginaryPart);
  return c;
} // end function add

Complex Complex::subtract( const Complex &right ) {
  Complex c;
  c.setComplexNumber(realPart - right.realPart, imaginaryPart - right.imaginaryPart);
  return c;
} // end function subtract

void Complex::printComplex() {
 std::cout << '(' << realPart << ", " << imaginaryPart << ')';
} // end function printComplex

void Complex::setComplexNumber( double rp, double ip ) {
 realPart = rp;
 imaginaryPart = ip;
} // end function setComplexNumber