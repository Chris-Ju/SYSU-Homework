#include "standard.hpp"
#include <iostream>
using namespace std;

D::D(int a, int b, int c, int d, int e):B(a, b),member(c, d),k(e)
{
}

void D::print() const
{
 cout << "Printing from Base:\n";
 B::print();
 cout << "Printing from member:\n";
 member.print();
 cout << "Printing from D field:\n";
 cout << k;
}