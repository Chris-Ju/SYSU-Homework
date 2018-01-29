#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;
using std::cin;

struct vector
{
    int x;
    int y;
};

class gameobject
{
public:
    virtual void select() const = 0;
    virtual void move() = 0;
    int get_hp()
    {
        return hp;
    }
    vector speed;
    vector site;
    int hp;

};

class worker: public gameobject
{
public:
    worker(int x, int y)
    {
        hp = 10;
        site.x = x;
        site.y = y;
        speed.x = 1;
        speed.y = 1;
    }
    virtual void select() const
    {
        cout << "Scv good to go, sir!" << endl;
    }
    virtual void move()
    {
        site.x += speed.x;
        site.y += speed.y;
        cout << "Worker moves to (" << site.x << ", " << site.y << ")"  << endl;
    }
    void build(int m)
    {
        for(int i = 1; i <= m; i++)
        {
            for(int j = i; j < m; j++)
                cout << " ";
            for(int j = 1; j <= 2 * i - 1; j++)
                cout << "*";
            cout << endl;
        }
    }
    void repair(gameobject* m)
    {
        m->hp = 10;
    }
};

class zealot: public gameobject
{
public:
    zealot(int x, int y)
    {
        hp = 10;
        site.x = x;
        site.y = y;
        speed.x = 2;
        speed.y = 2;
    }
    virtual void select() const
    {
        cout << "My life for Aiur!" << endl;
    }
    virtual void move()
    {
        site.x += speed.x;
        site.y += speed.y;
        cout << "Zealot moves to (" << site.x << ", " << site.y << ")" << endl;
    }
    void attack(gameobject* m)
    {
        (m->hp)--;
    }
};

class tower: public gameobject
{
public:
    tower(int x, int y)
    {
        hp = 10;
        site.x = x;
        site.y = y;
        speed.x = 2;
        speed.y = 2;
    }
    virtual void select() const
    {
        cout << "~" << endl;
    }
    virtual void move()
    {
        cout << "Tower cannot move." << endl;
    }
    void attack(gameobject* m)
    {
        (m->hp)--;
    }
};

#endif // HEAD_H
