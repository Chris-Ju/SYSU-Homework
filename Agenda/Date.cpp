#include "Date.hpp"
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>

using std::string;

Date::Date()
{
    m_year = 0;
    m_month = 0;
    m_day = 0;
    m_hour = 0;
    m_minute = 0;
}


Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
    m_year = t_year;
    m_month = t_month;
    m_day = t_day;
    m_hour = t_hour;
    m_minute = t_minute;
}

bool isTrue(char m)
{
    if(m > '9' || m < '0')
        return false;
    return true;
}

Date::Date(const string &dateString)
{
    *this = stringToDate(dateString);
}


int Date::getYear(void) const
{
    return m_year;
}

void Date::setYear(const int t_year)
{
    m_year = t_year;
}

int Date::getMonth(void) const
{
    return m_month;
}

void Date::setMonth(const int t_month)
{
    m_month = t_month;
}

int Date::getDay(void) const
{
    return m_day;
}

void Date::setDay(const int t_day)
{
    m_day = t_day;
}

int Date::getHour(void) const
{
    return m_hour;
}

void Date::setHour(const int t_hour)
{
    m_hour = t_hour;
}

int Date::getMinute(void) const
{
    return m_minute;
}

void Date::setMinute(const int t_minute)
{
    m_minute = t_minute;
}

bool Date::isValid(const Date &t_date)
{
    int year = t_date.getYear();
    int month = t_date.getMonth();
    int day = t_date.getDay();
    int hour = t_date.getHour();
    int minute = t_date.getMinute();
    int k[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(year < 1000 || year > 9999)
        return false;
    if(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        k[1]++;
    if(month > 12 || month < 1)
        return false;
    if(day > k[month - 1] || day < 1)
        return false;
    if(hour > 23 || hour < 0)
        return false;
    if(minute > 59 || minute < 0)
        return false;
    return true;
}

Date Date::stringToDate(const string &dateString)
{
    Date bri;
    bool value = true;
    if(dateString.length() != 16 || dateString[4] != '-' || dateString[7] != '-'
        || dateString[10] != '/' || dateString[13] != ':')
        value = false;
    char tmp;
    for(int i = 0; i < 16; i++)
    {
        tmp = dateString[i];
        if(i != 4 && i != 7 && i != 10 && i != 13)
        {
            if(!isTrue(tmp))
            {
                value = false;
                break;
            }
        }
    }
    if(value)
    {
        bri.m_year = (dateString[0] - 48) * 1000 + (dateString[1] - 48) * 100 + 
            (dateString[2] - 48) * 10 + dateString[3] - 48;
        bri.m_month = (dateString[5] - 48) * 10 + (dateString[6] - 48);
        bri.m_day = (dateString[8] - 48) * 10 + dateString[9] - 48;
        bri.m_hour = (dateString[11] - 48) * 10 + dateString[12] - 48;
        bri.m_minute = (dateString[14] - 48) * 10 + dateString[15] - 48;
    }
    return bri;
}

string Date::dateToString(const Date &t_date)
{
    if(!isValid(t_date))
        return "0000-00-00/00:00";
    int year = t_date.getYear();
    int month = t_date.getMonth();
    int day = t_date.getDay();
    int hour = t_date.getHour();
    int minute = t_date.getMinute();
    char bri[17];
    memset(bri, 0, 17);
    sprintf(bri, "%04d-%02d-%02d/%02d:%02d", year, month, day, hour, minute);
    string tmp = bri;
    return tmp;
}

Date& Date::operator=(const Date &t_date)
{
    m_year = t_date.m_year;
    m_month = t_date.m_month;
    m_day = t_date.m_day;
    m_hour = t_date.m_hour;
    m_minute = t_date.m_minute;
    return *this;
}

bool Date::operator==(const Date &t_date) const
{
    if(m_hour == t_date.m_hour && m_minute == t_date.m_minute
        && m_day == t_date.m_day && m_month == t_date.m_month
        && m_year == t_date.m_year)
        return true;
    return false;
}

bool Date::operator>(const Date &t_date) const
{
    if(m_year > t_date.m_year)
        return true;
    else if(m_year == t_date.m_year)
    {
        if(m_month > t_date.m_month)
            return true;
        else if(m_month == t_date.m_month)
        {
            if(m_day > t_date.m_day)
                return true;
            else if(m_day == t_date.m_day)
            {
                if(m_hour > t_date.m_hour)
                    return true;
                else if(m_hour == t_date.m_hour)
                {
                    if(m_minute > t_date.m_minute)
                        return true;
                }
            }
        }
    }
    return false;
}
bool Date::operator<(const Date &t_date) const
{
    if(m_year < t_date.m_year)
        return true;
    else if(m_year == t_date.m_year)
    {
        if(m_month < t_date.m_month)
            return true;
        else if(m_month == t_date.m_month)
        {
            if(m_day < t_date.m_day)
                return true;
            else if(m_day == t_date.m_day)
            {
                if(m_hour < t_date.m_hour)
                    return true;
                else if(m_hour == t_date.m_hour)
                {
                    if(m_minute < t_date.m_minute)
                        return true;
                }
            }
        }
    }
    return false;
}
bool Date::operator>=(const Date &t_date) const
{
    if(m_year > t_date.m_year)
        return true;
    else if(m_year == t_date.m_year)
    {
        if(m_month > t_date.m_month)
            return true;
        else if(m_month == t_date.m_month)
        {
            if(m_day > t_date.m_day)
                return true;
            else if(m_day == t_date.m_day)
            {
                if(m_hour > t_date.m_hour)
                    return true;
                else if(m_hour == t_date.m_hour)
                {
                    if(m_minute >= t_date.m_minute)
                        return true;
                }
            }
        }
    }
    return false;
}

bool Date::operator<=(const Date &t_date) const
{
    if(m_year < t_date.m_year)
        return true;
    else if(m_year == t_date.m_year)
    {
        if(m_month < t_date.m_month)
            return true;
        else if(m_month == t_date.m_month)
        {
            if(m_day < t_date.m_day)
                return true;
            else if(m_day == t_date.m_day)
            {
                if(m_hour < t_date.m_hour)
                    return true;
                else if(m_hour == t_date.m_hour)
                {
                    if(m_minute <= t_date.m_minute)
                        return true;
                }
            }
        }
    }
    return false;
}