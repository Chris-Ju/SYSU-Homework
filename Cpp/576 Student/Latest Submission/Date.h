#ifndef DATE_H
#define DATE_H


#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Date
{
private:
    int _year;
    int _month;
    int _day;
public:
    Date(int y, int m, int d)
    {
        _year = y;
        _month = m;
        _day = d;
    }
    Date(string dateString)
    {
        int i, j = 0, k = 0;
        int date[3];
        char tmp[5];
        memset(tmp, 0, 5);
        dateString = dateString + "-";
        for(i = 0; i < dateString.length(); i++)
        {
            if(dateString[i] == '-')
            {
                date[j++] = atoi(tmp);
                memset(tmp, 0, 5);
                k = 0;
            }
            else
                tmp[k++] = dateString[i];
        }
        _year = date[0];
        _month = date[1];
        _day = date[2];
    }
    int getYear() const
    {
        return _year;
    }
    int getMonth() const
    {
        return _month;
    }
    int getDay() const
    {
        return _day;
    }

    void setYear(int y)
    {
        _year = y;
    }
    void setMonth(int m)
    {
        _month = m;
    }
    void setDay(int d)
    {
        _day = d;
    }

    bool operator==(Date& other) const
    {
        if(_year != other.getYear() || _month != other.getMonth() || _day != other.getDay())
            return false;
        return true;
    }

    bool operator<(Date& other) const
    {
        bool val = false;
        if(_year == other.getYear())
        {
            if(_month == other.getMonth())
            {
                if(_day < other.getDay())
                    val = true;
            }
            else if(_month < other.getMonth())
                val = true;
        }
        else if(_year < other.getYear())
            val = true;
        return val;
    }
    bool operator>(Date& other) const
    {
        bool val = false;
        if(_year == other.getYear())
        {
            if(_month == other.getMonth())
            {
                if(_day > other.getDay())
                    val = true;
            }
            else if(_month > other.getMonth())
                val = true;
        }
        else if(_year > other.getYear())
            val = true;
        return val;
    }

    string toString() const
    {
        char m[20];
        memset(m, 0, 20);
        sprintf(m, "%d-%d-%d", _year, _month, _day);
        string k = m;
        return k;
    }

};

#endif // DATE_H
