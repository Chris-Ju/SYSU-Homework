#include<iostream>
#include<string>

std::string change1(const char* cstr);
void change2(std::string str, char* cstr);
std::string change1(const char* cstr)
 {
   std::string str = cstr;
   return str;
 }

void change2(std::string str, char* cstr)
{
  int i;
   for( i = 0;i < str.length(); i++)
       cstr[i] = str[i];
  cstr[i] = 0;
}