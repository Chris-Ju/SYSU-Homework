#include<iostream>

class Complex
 {
 public:
  Complex( double , double  );
  Complex();
  Complex add( const Complex &right ) ;
  Complex subtract( const Complex &right );
  void printComplex();
  void setComplexNumber( double , double  );
 private:
  double realPart;
  double imaginaryPart;
 };