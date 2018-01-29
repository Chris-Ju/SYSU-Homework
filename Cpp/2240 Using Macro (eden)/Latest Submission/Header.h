#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cmath>
#include <cstring>

#define MAX 100
#define MIN -100
#define max(a, b) (a) > (b)? (a):(b)
#define square(a) (a) * (a)
#define e(a, b) (a) * pow(10, b)
#define mstr(m) str(m)
#define str(st) #st
#define WARN_IF(m) cout << (m ? str(Warning: m):"\n")

#endif // HEADER_H
