#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>

using std::cout;
using std::endl;

enum Type {
    CAT,
    DOG
};

class Animal {
 public:
    Animal(){};
    Animal(std::string _name, int _age) : name(_name), age(_age) {}
    virtual void Shout() const = 0;
    virtual Type getType() const = 0;
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

 private:
    std::string name;
    int age;
};

class Cat:public Animal
{
public:
    Cat(){};
    Cat(std::string _name, int _age):Animal(_name, _age){};
    virtual void Shout() const
    {
        cout << getName() << ": meow~~" << endl;
    }
    virtual Type getType() const
    {
        return CAT;
    }
};


class Dog:public Animal
{
public:
    Dog(){};
    Dog(std::string _name, int _age):Animal(_name, _age){};
    virtual void Shout() const
    {
        cout << getName() << ": bark!!" << endl;
    }
    virtual Type getType() const
    {
        return DOG;
    }
};
#endif // ANIMAL_H
