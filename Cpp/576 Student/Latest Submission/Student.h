#ifndef STUDENT_H
#define STUDENT_H


#include "Date.h"
#include "Person.h"
#include <iostream>
using namespace std;

Date today(2017, 5, 7);
class Student:public Person
{
public:
    Student(string name, int age, Date g):Person(name, age), graduateDate(g)
    {
        this->name = name;
        this->age = age;
    }
    virtual void sayHi() const
    {
        cout << "Hi, My name is " << name << ". I'm " << age << " years old." << endl;
        if(graduateDate > today)
        {
            cout << "I will graduate on " << graduateDate.toString() << ".\n";
        }
        else if(graduateDate == today)
        {
            cout << "I graduated today!\n";
        }
        else
        {
            cout << "I have graduated on " << graduateDate.toString() << ".\n";
        }
    }
    void set(int age)
    {
        this->age = age;
    }
    void set(string name)
    {
        this->name = name;
    }
    void set(Date g)
    {
        graduateDate.setYear(g.getYear());
        graduateDate.setMonth(g.getMonth());
        graduateDate.setDay(g.getDay());

    }
private:
    Date graduateDate;
    string name;
    int age;

};

#endif // STUDENT_H
