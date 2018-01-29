 #include <cstring>
#include "Biginteger.h"
using namespace std;

BigInteger::BigInteger()
{
    int *data_ = NULL;
    size_ = 0;
}

BigInteger::BigInteger(const string& number)
{
    int n = number.length();
    size_ = n;
    int *node = new int[n];
    memset(node, 0, sizeof(int) * n);
    for(int i = 0; i < n ; i++)
        node[n - i - 1] = number[i] - 48;
    data_ = node;
    //for(int i = 0; i < n ; i++)
        //cout << data_[n - i - 1];
    //cout << endl;
}

BigInteger::BigInteger(const BigInteger& other)
{
    size_ = other.size_;
    int *node = new int[size_];
    memset(node, 0, sizeof(int) * size_);
    for(int i = 0; i < size_; i++)
        node[i] = other.data_[i];
    this->data_ = node;
    //for(int i = 0; i < size_ ; i++)
        //cout << other.data_[size_ - i - 1];
    //cout << endl;
}

BigInteger::~BigInteger()
{
    delete[] data_;
    data_ = NULL;
}

BigInteger operator+(const BigInteger& left, const BigInteger& right)
{

    /*for(int i = 0; i < left.size_ ; i++)
        cout << left.data_[left.size_ - i - 1];
    cout << endl;
	for(int i = 0; i < right.size_ ; i++)
        cout << right.data_[right.size_ - i - 1];
    cout << endl;*/
    //cout << left.size_ << endl;
	BigInteger tmp;
    int i,add = 0;
    if(left.size_ < right.size_)
    {   
        int *node = new int[right.size_ + 1];
        tmp.data_ = node;
        memset(tmp.data_, 0, sizeof(int) * (right.size_ + 1));
        tmp.size_ = right.size_ + 1;
        for(i = 0; i < left.size_ ; i++)
        {
            tmp.data_[i] = left.data_[i] + right.data_[i] + add;
            tmp.data_[i] %= 10;
            add = (left.data_[i] + right.data_[i] + add) / 10;
        }
        while(i < right.size_)
        {
            tmp.data_[i] = right.data_[i] + add;
            tmp.data_[i] %= 10;
            add = (right.data_[i] + add) / 10;
            i++;
        }
    }
    else
    {
	    int *node = new int[left.size_ + 1];
        tmp.data_ = node;
        memset(tmp.data_, 0, sizeof(int) * (left.size_ + 1));
        tmp.size_ = left.size_ + 1;
        for(i = 0; i < right.size_ ; i++)
        {
            tmp.data_[i] = left.data_[i] + right.data_[i] + add;
            tmp.data_[i] %= 10;
            add = (left.data_[i] + right.data_[i] + add) / 10;
            //cout << tmp.data_[i] << endl;
        }
        while(i < left.size_)
        {
            tmp.data_[i] = left.data_[i] + add;
            tmp.data_[i] %= 10;
            add = (left.data_[i] + add) / 10;
            //cout <<tmp.data_[i] << endl;
            i++;

        }
    }
    if(add == 1)
        tmp.data_[i] = 1;
    else
        tmp.size_--;
    //for(i = 0; i < tmp.size_; i++)
        //cout << tmp.data_[tmp.size_ - 1 - i];
	//cout << endl;
    return tmp;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right)
{
    BigInteger tmp;
    int i,sub = 0;
    if(left.size_ < right.size_)
    { 
        int *node = new int[right.size_];
        tmp.data_ = node;
        memset(tmp.data_, 0, sizeof(int) * right.size_);
        tmp.size_ = right.size_;
        for(i = 0; i < left.size_ ; i++)
        {
            tmp.data_[i] = right.data_[i] - left.data_[i] + sub;
            if(tmp.data_[i] < 0)
                tmp.data_[i] += 10;
            sub = (right.data_[i] - left.data_[i] + sub - 9) / 10;
            //cout << tmp.data_[i] << endl;
        }
        while(i < right.size_)
        {
            tmp.data_[i] = right.data_[i] + sub;
            if(tmp.data_[i] < 0)
                tmp.data_[i] += 10;
            sub = (right.data_[i] + sub - 9) / 10;
            i++;
        }
        i = tmp.size_ - 1;
        while(i >= 1)
        {    
            if(tmp.data_[i] == 0)
                tmp.size_--;
            else
                break;
            i--;
        }
        tmp.data_[i] = -tmp.data_[i];
    }
	else if(left.size_ > right.size_)
    {
        int *node = new int[left.size_];
        tmp.data_ = node;
        memset(tmp.data_, 0, sizeof(int) * left.size_);
        tmp.size_ = left.size_;
        int i,sub = 0;
        for(i = 0; i < right.size_ ; i++)
        {
            tmp.data_[i] = left.data_[i] - right.data_[i] + sub;
		    if(tmp.data_[i] < 0)
                tmp.data_[i] += 10;
            sub = (left.data_[i] - right.data_[i] + sub - 9) / 10;
           
        }
        while(i < left.size_)
        {
            tmp.data_[i] = left.data_[i] + sub;
		    if(tmp.data_[i] < 0)
                tmp.data_ += 10;
            sub = (left.data_[i] + sub - 9) / 10;
            i++;
        }
        i = tmp.size_ - 1;
        while(i >= 1)
        {    
            if(tmp.data_[i] == 0)
                tmp.size_--;
            else
                break;
            i--;
        }
        //cout << tmp.size_ << endl;
    }
    else
    {
        int m = 1;
        for(int j = 0; j < left.size_ ; j++)
            if(left.data_[j] < right.data_[j])
                m = -1;

        int *node = new int[left.size_];
        tmp.data_ = node;
        memset(tmp.data_, 0, sizeof(int) * left.size_);
        tmp.size_ = left.size_;;
        int i,sub = 0;
        for(i = 0; i < left.size_ ; i++)
        {
            tmp.data_[i] = m * left.data_[i] - m * right.data_[i] + sub;
		    if(tmp.data_[i] < 0 && i != left.size_ - 1)
                tmp.data_[i] += 10;
            sub = (m * left.data_[i] - m * right.data_[i] + sub - 9) / 10;
            //cout << sub << " " << tmp.data_[i] << endl;
        }
        i = tmp.size_ - 1;
        while(i >= 1)
        {    
            if(tmp.data_[i] == 0)
                tmp.size_--;
            else
                break;
            i--;
        }
        if(m == -1)
            tmp.data_[i] = -tmp.data_[i];
        //cout << tmp.size_ << endl;
    }
    //for(i = 0; i < tmp.size_; i++)
        //cout << tmp.data_[tmp.size_ - 1 - i];
	//cout << endl;
    return tmp;
}

ostream& operator<<(ostream& out, const BigInteger& Bint)
{
    
    for(int i = 0; i < Bint.size_; i++)
        out << Bint.data_[Bint.size_ - i - 1];
    return out;
}