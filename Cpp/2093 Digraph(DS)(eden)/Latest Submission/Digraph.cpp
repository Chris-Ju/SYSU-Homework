#include "Digraph.hpp"
#include "ProductSet.hpp"
#include "Matrix.hpp"
#include "Set.hpp"

Digraph::Digraph(BooleanMatrix const &m, Set const &s):Relation(m), set(s)
{
}

int Digraph::getSetElePos(int n)
{
    for(int i = 1; i <= set.getSize(); i++)
    {
        if(set.get(i) == n)
            return i;
    }
    return -1;
}

int Digraph::inDegree(int n)
{
    int m = getSetElePos(n);
    int count = 0;
    int columns = set.getSize();
    if(m == -1)
        return -1;
    else
    {
        for(int i = 1; i <= columns; i++)
        {
            if(Relation::matrix.Matrix::getElement(i, m))
                count++;
        }
        return count;
    }
}

int Digraph::outDegree(int n)
{
    int m = getSetElePos(n);
    int count = 0;
    int columns = set.getSize();
    if(m == -1)
        return -1;
    else
    {
        for(int i = 1; i <= columns; i++)
        {
            if(Relation::matrix.Matrix::getElement(m, i))
                count++;
        }
        return count;
    }
}


Digraph Digraph::pathOfLength(int times)
{
    BooleanMatrix tmp(Relation::matrix);
    //tmp.display();
    for(int i = 1; i < times; i++)
        tmp = tmp.BooleanProduct(tmp);
    //tmp.display();
    Digraph result(tmp, set);
    return result;
}

bool Digraph::isReflexive() const
{
    if(!Relation::matrix.isSquareMatrix())
        return false;
    Set tmp = set;
    int columns = tmp.getSize();
    for(int i = 1; i <= columns; i++)
    {
        if(!Relation::matrix.Matrix::getElement(i, i))
            return false;
    }
    return true;
}

bool Digraph::isIrreflexive() const
{
    if(!Relation::matrix.isSquareMatrix())
        return false;
    Set tmp = set;
    int columns = tmp.getSize();
    for(int i = 1; i <= columns; i++)
    {
        if(Relation::matrix.Matrix::getElement(i, i))
            return false;
    }
    return true;
}

bool Digraph::isSymmetric() const
{
    Set tmp = set;
    int columns = tmp.getSize();
    for(int i = 1; i <= columns; i++)
    {
        for(int j = i + 1; j <= columns; j++)
        {
            if(!Relation::matrix.Matrix::getElement(i, j) == Relation::matrix.Matrix::getElement(j, i))
                return false;
        }
    }
    return true;
   
}

bool Digraph::isAsymmetric() const
{
    Set tmp = set;
    int columns = tmp.getSize();
    if(columns == 1)
        return true;
    for(int i = 1; i <= columns; i++)
    {
        if(Relation::matrix.Matrix::getElement(i, i))
            return false;
        for(int j = i + 1; j <= columns; j++)
        {
            if(Relation::matrix.Matrix::getElement(i, j) == Relation::matrix.Matrix::getElement(j, i))
                return false;

        }
    }
    return true;
}

bool Digraph::isAntisymmetric() const
{
    Set tmp = set;
    int columns = tmp.getSize();
    for(int i = 1; i <= columns; i++)
    {
        for(int j = i + 1; j <=columns; j++)
        {
            if(Relation::matrix.Matrix::getElement(i, j))
            {
			    if(Relation::matrix.Matrix::getElement(j, i))
                    return false;
			}
        }
    }
    return true;
}

bool Digraph::isTransitive() const
{
    if(!Relation::matrix.isSquareMatrix())
        return false;
    Set tmp = set;
    int columns = tmp.getSize();
    for(int i = 1; i <= columns; i++)
    {
        for(int j = 1; j <= columns; j++)
        {
            if(j == i)
                continue;
            if(Relation::matrix.Matrix::getElement(i, j))
            {
                for(int k = 1; k <= columns; k++)
                {
                    if(j == k)
                        continue;
                    if(Relation::matrix.Matrix::getElement(j, k))
                        if(!Relation::matrix.Matrix::getElement(i, k))
                            return false;
                }
            }
        }
    }
    return true;
}

BooleanMatrix Digraph::getBooleanMatrix() const
{
    return Relation::matrix;
}

