#include "Matrix.h"
int add(int* n, int** m, int length , int j);

Matrix::Matrix(string name, int height, int width, int** param)
{
    this->name = name;
    this->height = height;
    this->width = width;
    int **mat = new int*[height];
    for (int i = 0; i < height; i++) 
    {
        mat[i] = new int[width];
        for (int j = 0; j < width; j++) 
        {
            mat[i][j] = param[i][j];
        }
    }
    this->param = mat;
}

Matrix::Matrix(const Matrix & node)
{
    name = node.name;
    height = node.height;
    width = node.width;
    int **mat = new int*[height];
    for (int i = 0; i < height; i++) 
    {
        mat[i] = new int[width];
        for (int j = 0; j < width; j++) 
        {
            mat[i][j] = node.param[i][j];
        }
    }
    this->param = mat;
}

Matrix::~Matrix()
{
    for (int i = 0; i < height; i++) 
    {
        delete [] param[i];
    }
    delete [] param;
}



bool Matrix::operator ==(const Matrix& node)
{
    if(width != node.width || height != node.height)
        return false;
    for(int i = 0; i < height ; i++)
        for(int j = 0; j < width ; j++)
        {
            if(param[i][j] != node.param[i][j])
                return false;
        }
    return true;
}

bool Matrix::operator !=(const Matrix& node)
{
    if(width != node.width || height != node.height)
        return true;
    for(int i = 0; i < height ; i++)
        for(int j = 0; j < width ; j++)
        {
            if(param[i][j] != node.param[i][j])
                return true;
        }
    return false;
}

void Matrix::operator +=(const Matrix& node)
{
    if(width != node.width || height != node.height)
    {
        cout << "invalid addition." << endl;
        return;
    }
    for(int i = 0; i < height ; i++)
        for(int j = 0; j < width ; j++)
        {
            param[i][j] += node.param[i][j];
        }
}

void Matrix::operator -=(const Matrix& node)
{
    if(width != node.width || height != node.height)
    {
        cout << "invalid substraction." << endl;
        return;
    }
    for(int i = 0; i < height ; i++)
        for(int j = 0; j < width ; j++)
        {
            param[i][j] -= node.param[i][j];
        }
}

Matrix Matrix::operator *(const Matrix& node)
{
    Matrix tmp;
    if(width != node.height)
    {
        cout << "invalid multiplication." << endl;
        return tmp;
    }
    int **mat = new int*[height];
    for (int i = 0; i < height; i++) 
    {
        mat[i] = new int[node.width];
        for (int j = 0; j < node.width; j++) 
        {
            mat[i][j] = add(param[i], node.param, width, j);
        }
    }
    tmp.name = "newMat";
    tmp.width = node.width;
    tmp.height = height;
    tmp.param = mat;
    return tmp;
}

int add(int* n, int** m, int length , int j)
{
    int result = 0;
    for(int i = 0; i < length; i++)
        result += n[i] * m[i][j];
    return result;
}


