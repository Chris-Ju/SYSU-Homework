 #include "Relation.hpp"
#include "BooleanMatrix.hpp"
#include "Matrix.hpp"

Relation::Relation(BooleanMatrix const &other):matrix(other)
{}

BooleanMatrix Relation::getBooleanMatrix() const
{
    return matrix;
}

Relation Relation::complementary() const
{
    BooleanMatrix n(matrix);
    for(int i = 1; i <= n.getRow(); i++)
    {
        for(int j = 1; j <= n.getColums(); j++)
            n.replace(!n.getElement(i, j), i, j);
    }
    Relation m(n);
    return m;
}

Relation Relation::inverse() const
{
    BooleanMatrix n(matrix.getColums(), matrix.getRow());
    for(int i = 1; i <= n.getRow(); i++)
    {
        for(int j = 1; j <= n.getColums(); j++)
        {
            n.replace(matrix.getElement(j, i), i, j);
        }
    }
    Relation m(n);
    return m;
}


Relation Relation::operator&(const Relation &other)
{
    BooleanMatrix n(other.matrix);
    n = n & matrix;
    return n;
}

Relation Relation::operator|(const Relation &other)
{
    BooleanMatrix n(other.matrix);
    n = n | matrix;
    return n;
}
