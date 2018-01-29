#include "SingleDog.h"
#include <cstring>
int SingleDog::count = 0;

SingleDog::SingleDog(int id_, char* name_):id(id_)
{
	this->name = new char[20];
	int i;
	for(i = 0; i < strlen(name_); i++)
	{
		this->name[i] = name_[i];
	}
	this->name[i] = 0;
	
	count++;
}
SingleDog::SingleDog(const SingleDog &other):id(other.id)
{
	count++;
	this->name = new char[20];
	int i;
	for(i = 0; i < strlen(other.name); i++)
	{
		this->name[i] = other.name[i];
	}
	this->name[i] = 0;
}
int SingleDog::getCount()
{
	return count;
}
SingleDog::~SingleDog()
{
	delete []this->name;
	count--;
}