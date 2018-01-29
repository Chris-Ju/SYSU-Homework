#include <iostream>
using namespace std;
class baseA
 {
   public:
    baseA();
   ~baseA();
 };
class baseB
{
public:
baseB();
~baseB();
};

class derivedA:public baseA
{
public:
derivedA();
~derivedA();
};
class derivedB:public baseA,baseB
{
public:
derivedB();
~derivedB();
};
class C:  public derivedA,derivedB
{
public:
C();
~C();
};