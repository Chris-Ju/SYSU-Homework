#include "VIPAccount.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int VIPAccount::_total_vip_account = 0;
int VIPAccount::_acc_id_ptr = 12050000;


VIPAccount::VIPAccount()
{
    _id = _acc_id_ptr;
    _total_vip_account++;
    _acc_id_ptr++;
    _loan = 0;
    _loan_limit = 1000;
    _balance = 10;
    _valid = true;
}
VIPAccount::~VIPAccount()
{
    _total_vip_account--;
}

void VIPAccount::reset()
{
    Account::reset();
    _loan = 0;
  		_loan_limit = 1000;
}

int VIPAccount::get_total_vip_account()
{
    return _total_vip_account;
}

std::string VIPAccount::profile() const
{
    /*std::string result = Account::profile(), tmp;
    result += "TYPE:VIP\nLOAN:";
    char str[100];
  		memset(str,0,100);
    sprintf(str, "%.6lf", _loan);
    tmp = str;
    result = result + tmp + ",LIMIT:";
  		memset(str,0,100);
    sprintf(str, "%.6lf", _loan_limit);
    tmp = str;
    result = result + tmp + "\n";
    return result;*/
  	char str[1000];
	memset(str, 0, sizeof(str));
	sprintf(str,"ID:%d\nBALANCE:%.6lf\nVALID:Y\nTYPE:VIP\nLOAN:%.6lf,LIMIT:%.6lf\n",_id, _balance, _loan, _loan_limit);
    return std::string(str);
}

bool VIPAccount::loan(const double &num)
{
    if(num + _loan >= _loan_limit)
        return false;
    _loan += num;
    _balance += num;
    return true;
}
bool VIPAccount::repay(const double &num)
{
    if(num > _balance - 0.01)
        return false;
    if(num > _loan)
    		return repay(_loan);  
  		_balance -= num;
    _loan -= num;
    return true;
}
