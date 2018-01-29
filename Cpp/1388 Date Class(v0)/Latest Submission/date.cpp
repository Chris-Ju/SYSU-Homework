 #include"date.hpp"


void Date::setDate(int year, int month, int day)
{
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::year() const
{
	return Date::year_;
}

int Date::month() const
{
	return Date::month_;
}

int Date::day() const
{
	return Date::day_;
}

int Date::daysOfMonth(int year, int month) const
{
	if(month % 2 != 0 && month <= 7)
   return 31;
 else if(month % 2 == 0 && month >= 8)
   return 31;
  else if(month != 2)
     return 30;
	if(year % 400 == 0 || year % 100 !=0 && year % 4 == 0 )
		return 29;
		return 28;
}

void Date::increment()
{
	if(day_ == Date::daysOfMonth(year_, month_))
	{
		if(month_ == 12)
		{
			month_ = 1;
			year_++;
			day_ = 1;
		}
		else
		{
			month_++;
			day_ = 1;
		}
	}
	else
	{
		day_++;
	}
}

void Date::decrement()
{
	if(day_ == 1)
	{
		if(month_ == 1)
		{
			month_ = 12;
			year_--;
			day_ = 31;
		}
		else
		{
			month_--;
			day_ = Date::daysOfMonth(year_, month_);
		}
	}
	else
		day_--;
}