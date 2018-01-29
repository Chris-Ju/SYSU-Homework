#ifndef SNAKE_H
#define SNAKE_H

#include "global.hpp"

class Snake
{
    public:
        Snake(){length = 1;}
        void setHead(point head)
        {
            body[0] = head;
        }
        void Smove(direction d, char Map[16][16], point size)
        {
            if(d == freeze)
                return;
            point tmp = body[0];
            body[0].move(d);
            if(body[0].x >= size.x || body[0].y >= size.y
            || body[0].x < 0 || body[0].y < 0)
                return;
            for(int i = 1; i < length - 1; i++)
            {
                if(body[0] == body[i])
                    return;
            }
            if(Map[body[0].x][body[0].y] == FOOD)
            {
                length++;
                Map[body[0].x][body[0].y] = HEAD;
                Map[tmp.x][tmp.y] = BODY;
                for(int i = length - 1; i > 1; i--)
                    body[i] = body[i - 1];
                body[1] = tmp;
                return;
            }
            else
            {
                Map[body[0].x][body[0].y] = HEAD;
                if(length == 1)
                {
                    Map[tmp.x][tmp.y] = EMPTY;
                    return;
                }
                Map[body[length - 1].x][body[length - 1].y] = EMPTY;
                for(int i = length - 1; i > 1; i--)
                    body[i] = body[i - 1];
                body[1] = tmp;
                Map[body[1].x][body[1].y] = BODY;    
                Map[body[0].x][body[0].y] = HEAD;
                return;
            }
        }
        bool isGameOver(point size)
        {
            if(body[0].x >= size.x || body[0].y >= size.y
            || body[0].x < 0 || body[0].y < 0)
                return true;
            for(int i = 1; i < length; i++)
            {
                if(body[0] == body[i])
                    return true;
            }
            return false;
        }
    private:
        point body[1000];
        int length;
};

#endif
