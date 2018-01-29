#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cstring>
#include "my_function.hpp"
using namespace std;

void buildLog(const string& k)
{
	int i = 0;
	ifstream log;
	char path[20]{0};
	while(1)
	{
		memset(path, 0, 20);
		sprintf(path, "Log%d.log", i);
		log.open(path);
		log.seekg(0, ios::end);
		streampos ps = log.tellg();
		if(ps > 1024 * 1024)
		{
			i++;
			log.close();
		}
		else
		{
			log.close();
			break;
		}
	}
	ofstream logfile(path, ios::app);
	logfile << getTime() << "\n";
	logfile << k << "\n\n";
	logfile.close();
}