 #include "Bitset.h"
#include <cmath>

bitset::bitset()
{
    for(int i = 0; i < N ; i++)
        a[i] = 0;
}

void bitset::set(int pos)
{
    int n = pos / 32;
    int m = pos % 32;
    a[n] = a[n] | (unsigned int)pow(2, m); 
}

void bitset::reset(int pos)
{
	
    int n = pos / 32;
    int m = pos % 32;
    a[n] = a[n] & ((unsigned int)0 -(unsigned int)1 - (unsigned int)pow(2, m));
}

int bitset::count() const
{
    int num = 0;
    int tmp;
    for(int i = 0; i < N ; i++)
    {
        tmp = a[i];
        for(int j = 0; j <= 31 ; j++)
        {
            if(tmp & 1)
            {
                num++;
            }
            tmp = tmp >> 1; 
        }
    }
    return num;
}

bool bitset::test(int pos) const
{
    int n = pos / 32;
    int m = pos % 32;
    if(a[n] & (int)pow(2, m))
        return true;
    return false;
}

bool bitset::any() const
{
    for(int i = 0; i < N ; i++)
    {
        if(a[i] != 0)
            return true;
    }
    return false;
}

bool bitset::none() const
{
    for(int i = 0; i < N ; i++)
    {
        if(a[i] != 0)
            return false;
    }
    return true;
}

bool bitset::all() const
{
    for(int i = 0; i < N ; i++)
    {
        if(a[i] != (int)pow(2, 32) - 1)
            return false;
    }
    return true;
}

bitset& bitset::operator&=(const bitset& b)
{
    for(int i = 0 ; i < N ; i++)
        a[i] = a[i] & b.a[i];
    return *this;
}


bitset& bitset::operator|=(const bitset& b)
{
    for(int i = 0 ; i < N ; i++)
        a[i] = a[i] | b.a[i];
    return *this;
}

bitset& bitset::operator^=(const bitset& b)
{
    for(int i = 0 ; i < N ; i++)
        a[i] = a[i] ^ b.a[i];
    return *this;
}

bitset& bitset::operator=(const bitset& b)
{
    for(int i = 0 ; i < N ; i++)
        a[i] = b.a[i];
    return *this;
}

bitset& bitset::operator <<= (int pos)
{
    int tmp;
    int add = 0;
    int m;
    for(int i = 0; i < N ; i++)
    {
        tmp = 0;
        for(int j = 0; j < pos; j++)
        {
            m = a[i] >> 31;
            if( j != 0 )
                tmp <<= 1;
            tmp += 1 & m;
            a[i] <<= 1;
        }
        a[i] |= add;
        add = tmp;
    } 
    return *this;
}
bitset& bitset::operator >>= (int pos)
{
    int tmp;
    int add = 0;
    int m;
    unsigned int b[N - 1] = {a[0], a[1], a[2], a[3]};
    for(int i = N - 1; i >= 0 ; i--)
    {
        tmp = 0;
        if(i == N - 1)
        {
            for(int j = 0; j < pos; j++)
            {
                m = a[i] & 1;
                tmp += (1 & m) * (int)pow(2, 31 - pos + j + 1);
                a[i] >>= 1;
            }
            a[i] |= add;
            add = tmp;
        }
        else
        {
            for(int j = 0; j < pos; j++)
            {
                m = b[i] & 1;
                tmp += (1 & m) * (int)pow(2, 31 - pos + j + 1);
                b[i] >>= 1;
            }
            b[i] |= add;
            add = tmp;
        }
    }
    for(int i = N - 2; i >= 0 ; i--)
    {
        a[i] = b[i];
    } 
    return *this;
}

bitset bitset::operator~() const
{
    bitset tmp;
    for(int i = 0; i < N ; i++)
        tmp.a[i] = ~a[i];
    return tmp;
}

bitset bitset::operator&(const bitset& b) const
{
    bitset tmp;
    for(int i = 0; i < N ; i ++)
        tmp.a[i] = a[i] & b.a[i];
    return tmp;
}

bitset bitset::operator|(const bitset& b) const
{
    bitset tmp;
    for(int i = 0; i < N ; i++)
        tmp.a[i] = a[i] | b.a[i];
    return tmp;
}

bitset bitset::operator^(const bitset& b) const
{
    bitset tmp;
    for(int i = 0; i < N ; i++)
        tmp.a[i] = a[i] ^ b.a[i];
    return tmp;
}


bitset bitset::operator<<(int pos) const
{
    bitset node;
    int tmp;
    int add = 0;
    int m;
    for(int i = 0; i < N ; i++)
    {
        node.a[i] = a[i];
        tmp = 0;
        for(int j = 0; j < pos; j++)
        {
            m = node.a[i] >> 31;
            if( j != 0 )
                tmp <<= 1;
            tmp += 1 & m;
            node.a[i] <<= 1;
        }
        node.a[i] |= add;
        add = tmp;
    } 
    return node;
}


bitset bitset::operator>>(int pos) const
{
    bitset node;
    int tmp;
    int add = 0;
    int m;
    for(int i = 0; i < N ;i++)
        node.a[i] = a[i];
    unsigned int b[N - 1] = {a[0], a[1], a[2], a[3]};
    for(int i = N - 1; i >= 0 ; i--)
    {
        tmp = 0;
        if(i == N - 1)
        {
            for(int j = 0; j < pos; j++)
            {
                m = node.a[i] & 1;
                tmp += (1 & m) * (int)pow(2, 31 - pos + j + 1);
                node.a[i] >>= 1;
            }
            node.a[i] |= add;
            add = tmp;
        }
        else
        {
            for(int j = 0; j < pos; j++)
            {
                m = b[i] & 1;
                tmp += (1 & m) * (int)pow(2, 31 - pos + j + 1);
                b[i] >>= 1;
            }
            b[i] |= add;
            add = tmp;
        }
    }
    for(int i = N - 2; i >= 0 ; i--)
    {
        node.a[i] = b[i];
    }
    return node;
}

bool bitset::operator== (const bitset& b) const
{
    for(int i = 0; i < N; i++)
        if(a[i] != b.a[i])
            return false;
    return true;
}


bool bitset::operator!= (const bitset& b) const
{
    int count = 0;
    for(int i = 0; i < N; i++)
        if(a[i] == b.a[i])
        {
            count++;
        }
    if(count == N)
        return false;
    return true;
}

bool bitset::operator[] (int pos) const
{
    int n = pos / 32;
    int m = pos % 32;
    if(a[n] & (int)pow(2, m))
        return true;
    return false; 
}
