#include "MyInteger.hpp"
#include <cstdlib>

MyInteger::MyInteger(int node)
{
	this->value = node;
}

int MyInteger::getValue() const
{
	return this->value;
}

bool MyInteger::isEven() const
{
	if(this->getValue() % 2 == 0)
		return true;
	return false;
}
bool MyInteger::isOdd() const
{
	if(this->getValue() % 2 != 0)
		return true;
	return false;
}
bool MyInteger::isPrime() const
{
	int i;
	if(this->getValue() == 2 && this->getValue() == 3)
		return true;
	for(i = 2; i * i <= this->getValue(); i++)
		if(this->getValue() % i == 0)
			return false;
	if(this->getValue() == 1)
		return false;
	return true;
}

bool MyInteger::isEven(int node)
{
	if(node % 2 == 0)
		return true;
	return false;
}
bool MyInteger::isOdd(int node)
{
	if(node % 2 != 0)
		return true;
	return false;
}
bool MyInteger::isPrime(int node)
{
	int i;
	if(node == 2 && node == 3)
		return true;
	for(i = 2; i * i <= node; i++)
		if(node % i == 0)
			return false;

	if(node == 1)
		return false;
	return true;
}

bool MyInteger::isEven(const MyInteger& node)
{
	if(node.getValue() % 2 == 0)
		return true;
	return false;
}
bool MyInteger::isOdd(const MyInteger& node)
{
	if(node.getValue() % 2 != 0)
		return true;
	return false;
}
bool MyInteger::isPrime(const MyInteger& node)
{
	int i;
	if(node.getValue() == 2 && node.getValue() == 3)
		return true;
	for(i = 2; i * i <= node.getValue(); i++)
		if(node.getValue() % i == 0)
			return false;
	if(node.getValue() == 1)
		return false;
	return true;
}

bool MyInteger::equals(int node)
{
	if(node == this->getValue())
		return true;
	return false;
}
bool MyInteger::equals(const MyInteger& node)
{
	if(this->getValue() == node.getValue())
		return true;
	return false;
}

int MyInteger::parseInt(const std::string& str)
{
	return atoi(str.c_str());
}
