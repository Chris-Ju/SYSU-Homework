#include <cstdio>
#include <ctime>
#include <string>
#include "my_function.hpp"

std::string getTime()
{
	time_t tt = time(NULL);
 	tm* t= localtime(&tt);
 	char date[50]{0};
 	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
 	return std::string(date);
}