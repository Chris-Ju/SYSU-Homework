#include "Complex.hpp"
#include <iostream>

using namespace std;
Complex::Complex()
{
	real = 0;
	imag = 0;
}
Complex::Complex(double a, double b)
{
	real = a;
	imag = b;
}
Complex::Complex(const Complex& node)
{
	real = node.real;
	imag = node.imag;
}

Complex& Complex::operator+=(const Complex& node)
{
	real += node.real;
	imag += node.imag;
	return *this;
}

Complex& Complex::operator-=(const Complex& node)
{
	real -= node.real;
	imag -= node.imag;
	return *this;
}
Complex& Complex::operator*=(const Complex& node)
{
	Complex tmp = *this;
	real = tmp.real * node.real - tmp.imag * node.imag;
	imag = tmp.real * node.imag + node.real * tmp.imag;
 return *this;
}

Complex& Complex::operator/=(const Complex& node)
{
	Complex a = *this;
	double tmp =  node.imag * node.imag + node.real * node.real;
	real = a.real * node.real + a.imag * node.imag;
	real /= tmp;
	imag = a.real * (-node.imag) + node.real * a.imag;
	imag /= tmp;
 return *this;

}

Complex Complex::operator+(const Complex& node)
{
	Complex bri;
	bri.real = node.real + real;
	bri.imag = node.imag + imag;
	return bri;
}

Complex Complex::operator-(const Complex& node)
{
	Complex bri;
	bri.real = -node.real + real;
	bri.imag = -node.imag + imag;
	return bri;
}

Complex Complex::operator*(const Complex& node)
{
	Complex bri;
	bri.real = real * node.real - imag * node.imag;
	bri.imag = real * node.imag + node.real * imag;
	return bri;
}

Complex Complex::operator/(const Complex& node)
{
	Complex bri;

	double tmp =  node.imag * node.imag + node.real * node.real;
	bri.real = real * node.real + imag * node.imag;
	bri.real /= tmp;
	bri.imag = real * (-node.imag) + node.real * imag;
	bri.imag /= tmp;
	return bri;

}
int Complex::operator==(const Complex& node)
{
	if(node.real != real || node.imag != imag)
		return 0;
	return 1;
}

int Complex::operator!=(const Complex& node)
{
	if(node.real != real || node.imag != imag)
		return 1;
	return 0;
}

ostream& operator<<(ostream& out, const Complex& node)
{

	if(node.real == 0 && node.imag != 0)
	{
		out << node.imag << "i" << endl;
		return out;
	}
	else if(node.imag == 0)
	{
		out << node.real;
		return out;
	}
	else if(node.imag < 0)
	{	
		out << node.real << node.imag << "i" << endl ;
		return out;
	}
	out << node.real << "+" << node.imag << "i" << endl;
	return out;
}	