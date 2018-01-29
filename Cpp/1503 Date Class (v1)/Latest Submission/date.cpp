 #include <iostream>
 #include "date.hpp"

 
 Date::Date()
 {
   setDate(2017, 1, 28);
 }
 Date::Date(int _year, int _month, int _day)
 {
   setDate(_year, _month, _day);
   Date::normalize();
 }

 bool Date::equals(const Date &comp) const
 {
   if(comp.year == year && comp.month == month && comp.day == day)
       return true;
   else
       return false;
 }

 bool Date::smallerThan(const Date &comp) const
 {
   if(year < comp.year)
       return true;
   else if(year == comp.year && month < comp.month)
       return true;
   else if(year == comp.year && month == comp.month && day < comp.day)
       return true;
   else
       return false;
 }

 void Date::normalize()
 {
   if(month > 12)
   {
       month -= 12;
       year ++;
       Date::normalize();
   }
   if(day > daysOfMonth(year, month))
   {
       int k = day - daysOfMonth(year, month);
       day = daysOfMonth(year, month);
       int i;
       for(i = 0;i < k;i++)
        increment();
       Date::normalize();
   }
 }

 

 