# A Class with Dual Role

# Description

There is a class B and another class D. Their relationship is as following:  
B is the base class of D and at the same time, D has a object member of the type of class B, as shown below. You should complete the definition of class D so that the main function can run successfully and its output as below.
```
#include <iostream>
using namespace std;

class B{
private:
int x;
int y;
public:
B(int a , int b){
x = a;
y = b;
}
void print() const {
cout<<x<<", "<<y<<endl;
}
};
class D: public B{
private:
B member;
  int c;
public:
// Your code will be included here.
};
int main(){
int i, j, m, n, k;
  cin>>i>>j>>m>>n>>k;
  D(i, j, m, n, k).print();
}
```

# Input
```
6 3 4 5 8
```
# Output
```
Printing from Base:
6, 3
Printing from member:
4, 5
Printing from D field:
8
```

# Hint
You need to define a constructor for D and redefine the print() function for D.  
**There is no '\n' at the end of output**