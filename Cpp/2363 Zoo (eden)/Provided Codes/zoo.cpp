#include "zoo.h"
#include "animal.h"


Zoo::Zoo()
{
    catnum = 0;
    dognum = 0;
}

void Zoo::addAnimal(Animal* m)
{
    std::vector<Animal*>::iterator item;
    for(item = animal.begin(); item != animal.end(); item++)
    {
        if((*item) == m)
            return;
    }
    animal.push_back(m);
    if(m->getType() == CAT)
        catnum++;
    else
        dognum++;
}
void Zoo::deleteAnimalByName(std::string m)
{
    std::vector<Animal*>::iterator item;
    for(item = animal.begin(); item != animal.end();item++)
    {
        if((*item)->getName() == m)
        {
            if((*item)->getType() == CAT)
                catnum--;
            else
                dognum--;
            animal.erase(item);
            item--;
        }
    }
}
void Zoo::deleteAnimalByAge(int m)
{
    std::vector<Animal*>::iterator item;
    for(item = animal.begin(); item != animal.end();item++)
    {
        if((*item)->getAge() == m)
        {
            if((*item)->getType() == CAT)
                catnum--;
            else
                dognum--;
            animal.erase(item);
            item--;
        }
    }
}
void Zoo::print()
{
    std::vector<Animal*>::iterator item;
    for(item = animal.begin(); item != animal.end(); item++)
    {
       (*item)->Shout();
    }
}
int Zoo::getDogCount()
{
    return dognum;
}

int Zoo::getCatCount()
{
    return catnum;
}
