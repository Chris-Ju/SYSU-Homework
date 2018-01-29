  #include "Account.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>


int Account::_total_account = 0;

Account::Account()
{
    _id = 0;
  		_total_account++;
    _balance = 0;
    _valid = false;
}

Account::~Account()
{
    _total_account--;
}
int Account::id() const
{
    return _id;
}
double Account::balance() const
{
    return _balance;
}
bool Account::valid() const
{
    return _valid;
}

void Account::reset()
{
    _balance = 10;
    _valid = true;
}

bool Account::deposit(const double &num)
{
    if(num < 0.01)
        return false;
    else
        _balance += num;
    if(!_valid)
        _valid = !_valid;
    return true;
}

bool Account::draw(const double &num)
{
    if( num < 0 || num > _balance - 0.01 || !_valid)
        return false;
    else
        _balance -= num;
    if(_balance < 0.01)
    {
        _valid = false;
    }
    return true;
}

int Account::get_total_account()
{
    return _total_account;
}

std::string Account::profile() const
{
    /*std::string result = "ID:", tmp;
    char str[100];
  		memset(str,0,100);
    sprintf(str,"%d", id());
    tmp = str;
    result = result + tmp + "\nBALANCE:";
  		memset(str,0,100);
    sprintf(str,"%.6lf", balance());
    tmp = str;
    result = result + tmp + "\nVALID:";
    if(valid())
        result += "Y\n";
    else
        result += "N\n";*/
  	char str[1000];
	memset(str, 0, sizeof(str));
	sprintf(str,"ID:%d\nBALANCE:%.6lf\nVALID:N\n",_id, _balance);
    return std::string(str);
}
