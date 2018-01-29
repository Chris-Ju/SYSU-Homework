#include <cstring>
#include <iostream>
#include <string>

using namespace std;
class String 
{
public:
String()
{
    _size = 0;
    _buff = NULL;
}
explicit String(const char *src)
{
    _buff = new char[20];
    memset(_buff, 0, 20);
    _size = strlen(src);
    for(int i = 0; i < _size; i++)
        _buff[i] = src[i];

}
String(const String &src)
{
    char* tmp = src.c_str();
    _buff = new char[20];
    memset(_buff, 0, 20);
    int m = strlen(tmp);
    _size = m;
    for(int i = 0; i < m; i++)
        _buff[i] = tmp[i];

}

~String()
{
    delete[] _buff;
}

String& operator =(const String& src)
{
    delete[] _buff;
    _buff = NULL;
    _size = 0;
    char* tmp = src.c_str();
    _buff = new char[20];
    memset(_buff, 0, 20);
    int m = strlen(tmp);
    _size = m;
    for(int i = 0; i < m; i++)
        _buff[i] = tmp[i];
    return *this;
}

char* c_str() const//return _buff
{
    return _buff;
}


friend ostream& operator <<(ostream& os, const String& src)
{
    string tmp = src.c_str();
    os << tmp;
    return os;
}

inline char& operator[](int m)
{
    return _buff[m];
}

private:
char *_buff;
int _size;
};

