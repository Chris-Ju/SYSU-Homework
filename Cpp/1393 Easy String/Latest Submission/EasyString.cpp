#include "EasyString.hpp"
#include <iostream>
#include <string>
using namespace std;

void Assign(char * &str, int &length)
{
	str = (char *)malloc(length + 1);
}

void AddTwo(string &str, char * &str1, char * &str2)
{
	  string str11 = str1;
  free(str1);
  string str22 = str2;
  free(str2);
  str = str11 + str22;
}