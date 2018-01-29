#ifndef MAP_H
#define MAP_H

#include "snake.hpp"
#include <list>
#include "global.hpp"
#include <iostream>

using std::cout;
using std::list;
using std::endl;


class map
{
    public:
        map(point initial_size, point initial_head, list<point> initial_foods)
        {
            this->size = initial_size;
            this->snake.setHead(initial_head);
            this->foods = initial_foods;
            for(int i = 0; i < size.x; i++)
                Map[i][size.y] = 0;
            Map[initial_head.x][initial_head.y] = HEAD;
            while(!foods.empty())
            {
                point tmp = foods.front();
                Map[tmp.x][tmp.y] = FOOD;
                foods.pop_front();
            }
        }
        ~map(){}
        void move(direction d)
        {
            snake.Smove(d, Map, size);
        }
        bool isGameOver()
        {
            return snake.isGameOver(size);
        }
        void print()
        {
            for(int i = 0; i < size.x; i++)
                cout << Map[i] << endl;
          cout << endl;
        }
    private:
        point size;
        list<point> foods;
        Snake snake;
        char Map[16][16] = {
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++",
            "+++++++++++++++"
        };
};


#endif