#include "String.h"
#include <cstring>
#include <string>

using std::string;

char _error_sign = 0;

void kmpValue(const string& n, int *kmpNext)
{
    int i = 0;
    int j = kmpNext[0] = -1;
    while( i < n.length())
    {
        while(j > -1 && n[i] != n[j])
            j = kmpNext[j];
        j++;
        i++;
        if(n[i] == n[j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

int kmp(const string& n, const string& m)
{
    //std::cout << m << std::endl << n << std::endl;
    if(n.length() > m.length())
        return -1;
    int *kmpNext = new int[n.length() + 1];
    memset(kmpNext, 0, sizeof(int) * (n.length() + 1));
    kmpValue(n, kmpNext);
    int i = 0;
    int j = 0;
    while(i < m.length())
    {
        if(j > -1 && m[i] != n[j])
            j = kmpNext[j];
        j++;
        i++;
        if(j >= n.length())
        {
            delete []kmpNext;
			return i - j;
        }
    }
    delete []kmpNext;
    return i;
}

String::String()
{
    _buff = NULL;
    _length = 0;
    _size = 1;
}

String::String(const char* src)
{
    int n = strlen(src);
    _length = n;
    _size = n + 1;
    _buff = new char[_size];
    strncpy(_buff, src, _size);
}

String::String(const String &src)
{
    _length = src._length;
    _size = src._size;
    _buff = new char[_size];
    strncpy(_buff, src._buff, _size);
}

String::~String()
{
    delete[] _buff;
    _buff = NULL;
}

void String::assign(const char *src)
{
    if(_buff != NULL)
        delete[] _buff;
    int n = strlen(src);
    _size = n + 1;
    _length = n;
    _buff = new char[_size];
    strncpy(_buff, src, _size);
}

void String::append(const char &other)
{
    char* str = new char[1 + _size];
    memset(str, 0, _size + 1);
    if(_buff != NULL)
        for(int i = 0; i < _length; i++)
            str[i] = _buff[i];
    str[_length] = other;
    if(_buff != NULL)
        delete[] _buff;
    _buff = str;
    _size++;
    _length++;
}

void String::clear()
{
    if(_buff != NULL)
        delete[] _buff;
    _buff = NULL;
    _length = 0;
    _size = 1;
}

int String::compare(const String &other) const
{
    int n = strcmp(_buff, other._buff);
    if(n > 0)
        return 1;
    else if(n < 0)
        return -1;
    else
        return 0;
}

const char* String::c_str() const
{
    return _buff;
}

bool String::empty() const
{
    if(_length == 0)
        return true;
    return false;
}

int String::find(const String &other, int pos) const
{
    /*char m[_size] = {0};
    for(int i = 0; i < _size; i++)
        m[i] = _buff[i];
    char n[other._size] = {0};
    for(int i = 0; i < other._size; i++)
        n[i] = other._buff[i];*/
    return kmp(other._buff, _buff);
}

int String::length() const
{
    return _length;
}

String String::substr(const int &pos, const int &count) const
{
    String n;
    n._buff = new char[count + 1];
    n._size = count + 1;
    memset(n._buff, 0, count + 1);
    int i;
    for(i = 0; i < count && _buff[i + pos] != 0; i++)
        n._buff[i] = _buff[i + pos];
    n._buff[i] = 0;
    n._length = i;
    return n;
}

char& String::operator[](const int &index)
{
    return _buff[index];
}

void String::operator=(const String &other)
{
    if(_buff != NULL)
        delete[] _buff;
    int n = other._length;
    _size = n + 1;
    _length = n;
    _buff = new char[_size];
    strncpy(_buff, other._buff, _size);
}

void String::operator=(const char *src)
{
    assign(src);
}

String String::operator+(const String &other) const
{
    String n;
    int m = _length + other._length;
    n._length = m;
    n._size = m + 1;
    n._buff = new char[m + 1];
    memset(n._buff, 0, m + 1);
    strcat(n._buff, _buff);
    strcat(n._buff, other._buff);
    return n;
}

bool String::operator<(const String &other) const
{
    if(strcmp(_buff, other._buff) < 0)
        return true;
    return false;
}

bool String::operator<=(const String &other) const
{
    if(strcmp(_buff, other._buff) <= 0)
        return true;
    return false;
}

bool String::operator>(const String &other) const
{
    if(strcmp(_buff, other._buff) > 0)
        return true;
    return false;
}

bool String::operator>=(const String &other) const
{
	if(strcmp(_buff, other._buff) >= 0)
        return true;
    return false;
}

bool String::operator==(const String &other) const
{
    if(strcmp(_buff, other._buff) == 0)
        return true;
    return false;
}

bool String::operator!=(const String &other) const
{
    if(strcmp(_buff, other._buff) != 0)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, const String &str)
{
    for(int i = 0;i < str._length; i++)
        out << str._buff[i];
    return out;
}

