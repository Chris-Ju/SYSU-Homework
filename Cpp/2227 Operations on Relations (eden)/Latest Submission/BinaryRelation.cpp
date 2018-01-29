#include "BinaryRelation.hpp"

#include "Matrix.hpp"

#include "BooleanMatrix.hpp"

#include "Set.hpp"



BinaryRelation::BinaryRelation(BooleanMatrix const &m, Set const &s):Relation(m),set(s)

{

}





int BinaryRelation::getSetElePos(int n)

{

    for(int i = 1; i <= set.getSize(); i++)

    {

        if(set.get(i) == n)

            return i;

    }

    return -1;

}



int BinaryRelation::inDegree(int n)

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



int BinaryRelation::outDegree(int n)

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





BinaryRelation BinaryRelation::pathOfLength(int times)

{

    BinaryRelation result(matrix, set);

    //tmp.display();

    for(int i = 1; i < times; i++)

        result.matrix = result.matrix.BooleanProduct(matrix);

    //tmp.display();

    return result;

}



bool BinaryRelation::isReflexive() const

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



bool BinaryRelation::isIrreflexive() const

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



bool BinaryRelation::isSymmetric() const

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



bool BinaryRelation::isAsymmetric() const

{

    Set tmp = set;

    int columns = tmp.getSize();
  		if(columns == 1 && matrix.getElement(1, 1) == 0)
        return true;

    if(!isSymmetric())

    {

        for(int i = 1; i <= columns; i++)

        {

            if(matrix.getElement(i, i))

                return false;

        }

        return true;

    }

    return false;

    /*

    if(columns == 1)

        return true;

    for(int i = 1; i <= columns; i++)

    {

        if(matrix.getElement(i, i))

            return false;

        for(int j = i + 1; j <= columns; j++)

        {

            if(matrix.getElement(i, j) == matrix.getElement(j, i))

                return false;



        }

    }*/

    //return true;

}



bool BinaryRelation::isAntisymmetric() const

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



bool BinaryRelation::isTransitive() const

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

bool BinaryRelation::isEquivalence() const

{

    if(isReflexive() && isSymmetric() && isTransitive())

        return true;

    return false;

}



BinaryRelation BinaryRelation::composition(const BinaryRelation &other)

{

    BooleanMatrix n(other.getBooleanMatrix());

    BinaryRelation m(n.BooleanProduct(getBooleanMatrix()), set);

    return m;

}



BinaryRelation BinaryRelation::reflexiveClosure() const

{

    BinaryRelation m(matrix, set);

    for(int i = 1; i <= matrix.getRow(); i++)

    {

        m.matrix.replace(true, i, i);

    }

    return m;

}



BinaryRelation BinaryRelation::symmetricClosure() const

{

    BinaryRelation m(matrix, set);

    for(int i = 1; i <= matrix.getRow(); i++)

    {

        for(int j = 1; j <= matrix.getColums(); j++)

        {

            if(matrix.getElement(i, j))

                m.matrix.replace(true, j, i);

        }

    }

    return m;

}



BinaryRelation BinaryRelation::transitiveClosure() const

{

    BinaryRelation m(matrix, set);

    for(int i = 1; i <= matrix.getRow(); i++)

	{

		for(int j = 1; j <= matrix.getColums(); j++)

		{

			if(m.matrix.getElement(i, j))

			{

				for(int k = 1; k <= matrix.getColums(); k++)

				{

					if(m.matrix.getElement(k, i))

					{

						m.matrix.replace(true, k, j);

					}

				}

			}

		}

	}

	return m;

}