#include "FUN.hpp"
#include <cstring>
#include <iostream>
using namespace std;

FUN::FUN(char *s)
{
 str = new char[strlen(s) + 1];
 memset(str, 0, sizeof(str));
 for(int i = 0; i < strlen(s); i++)
  str[i] = s[i];
}

FUN::FUN(const FUN& C)
{
 char* s = C.str;
 str = new char[strlen(s) + 1];
 memset(str, 0, sizeof(str));
 for(int i = 0; i < strlen(s); i++)
  str[i] = s[i];
}

void FUN::show()
{
 cout << str << endl;
}