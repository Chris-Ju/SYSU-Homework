#ifndef INSERVICE
#define INSERVICE
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Person
{
public:
	Person()
	{
		cout << "Construct Person" << endl;
	}
	~Person()
	{
		cout << "Destruct Person" << endl;
	}
	string getName()
	{
		return name;
	}
	int getSex()
	{
		return sex;
	}
	string getSno()
	{
		return sno;
	}
	string getWno()
	{
		return wno;
	}
	string name;
	int sex;
	string sno;
	string wno;
};

class Student:virtual public Person
{
	public:
	Student()
	{
		cout << "Construct Student" << endl;
	}
	~Student()
	{
		cout << "Destruct Student" << endl;	
	}
};

class Worker:virtual public Person
{
	public:
	Worker()
	{
		cout << "Construct Worker" << endl;
	}
	~Worker()
	{
		cout << "Destruct Worker" << endl;
	}
};

class InService:public Student,public Worker
{
	public:
	InService(string name, int sex, string sno, string wno)
	{
		this->name = name;
		this->sex = sex;
		this->sno = sno;
		this->wno = wno;
		cout << "Construct InService" << endl;
	}
	~InService()
	{
		cout << "Destruct InService" << endl;
	}
};
#endif