# Student

# Description
You are given a defintion of class `Person`. 

Person has :
* two member variables, `name` and `age`
* two overload function `set`, change the member variables accroding to the parameter
* a function `sayHi`, print some messages

**(see `Person.h` for detail)**

You should implement two class `Date` and `Student`

class `Date` : 
```
class Date {
  private:
    int _year;
    int _month;
    int _day;
  public:
    Date(int y, int m, int d);
    Date(string dateString); // the format of dateString is like "2017-5-7"
    int getYear() const;
    void setYear(int y);
    int getMonth() const;
    void setMonth(int m);
    int getDay() const;
    void setDay(int d);
    bool operator==(Date& other) const;
    bool operator<(Date& other) const;
    bool operator>(Date& other) const;
    std::string toString() const; // return a string like "year-month-day"
};
```

`Student` derive from `Person`, it has:
* a new member variables, `graduateDate`, means when the Student graduate
* a overloaded function `set(Date d)`, which changes the `graduateDate` to parameter `d`
* a overrided function `sayHi`, it should do the same thing as `sayHi` in Person first, and then:
	* if its `graduateDate` > today(`2017-5-7`), output `"I will graduate on year-month-day."`
	* if its `graduateDate` == today(`2017-5-7`), output `"I graduated today!"`
	* if its `graduateDate` < today(`2017-5-7`), output `"I have graduated on year-month-day."`

See the **sample output** for detail

## Sample Input
```
2014-5-4
Tom
25
2018 6 1
John
28
```
## Sample Output
```
2014-5-4 == 2014-5-4
2014-5-3 < 2014-5-4
2014-5-4 > 2014-5-3
Hi, My name is Tom. I'm 25 years old.
I have graduated on 2014-5-4.
Hi, My name is John. I'm 28 years old.
I will graduate on 2018-6-1.
```

## Hint
Be careful of `name hiding` in inheritance
