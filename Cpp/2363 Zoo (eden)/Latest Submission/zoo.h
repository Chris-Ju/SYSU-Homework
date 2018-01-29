 #ifndef ZOO_H
#define ZOO_H

#include "animal.h"
#include <vector>

class Zoo
{
public:
    Zoo();
    void addAnimal(Animal* m);
    void deleteAnimalByName(std::string m);
    void deleteAnimalByAge(int m);
    void print();
    int getDogCount();
    int getCatCount();

private:
    int dognum;
    int catnum;
    std::vector<Animal*> animal;
};

#endif // ZOO_H
