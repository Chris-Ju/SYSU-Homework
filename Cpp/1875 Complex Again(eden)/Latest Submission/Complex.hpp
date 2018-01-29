#include <iostream>
using namespace std;

class Complex {

	friend ostream &operator<<(std::ostream& out, const Complex&);
      //A friend function to print Complex numbers like a+bi where a is the real part and b is the imaginary part

public:
   Complex();
   Complex(double, double);
   Complex(const Complex&);

   //Some function about operator overloading.
   Complex& operator+=(const Complex& );
   Complex& operator-=(const Complex& );
   Complex& operator*=(const Complex& );
   Complex& operator/=(const Complex& );
   Complex operator+(const Complex& );
   Complex operator-(const Complex& );
   Complex operator*(const Complex& );
   Complex operator/(const Complex& );
   int operator==(const Complex& );
   int operator!=(const Complex& );
   


   void SetReal(double re){real = re;}
   void SetImag(double im){imag = im;}
private:
   double real; 
   double imag; 
};

