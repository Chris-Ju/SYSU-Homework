 #ifndef RELATION_H
#define RELATION_H

#include "ProductSet.hpp"
#include "BooleanMatrix.hpp"
#include "Set.hpp"

class Relation
{
    protected:
        BooleanMatrix matrix;
    public:
        Relation(BooleanMatrix const &m);
};


#endif