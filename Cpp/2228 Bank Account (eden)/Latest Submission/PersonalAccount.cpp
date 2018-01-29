#include "PersonalAccount.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int PersonalAccount::_total_per_account = 0;
int PersonalAccount::_acc_id_ptr = 12010000;

PersonalAccount::PersonalAccount()
{
    _total_per_account++;
    _id = _acc_id_ptr;
    _acc_id_ptr++;
    _balance = 10;
    _valid = true;
}
PersonalAccount::~PersonalAccount()
{
    _total_per_account--;
}
void PersonalAccount::reset()
{
    Account::reset();
}

int PersonalAccount::get_total_per_account()
{
    return _total_per_account;
}

std::string PersonalAccount::profile() const
{
    char str[1000];
  	memset(str, 0, sizeof(str));
	sprintf(str,"ID:%d\nBALANCE:%.6lf\nVALID:Y\nTYPE:PERSONAL\n", _id, _balance);
    return std::string(str);
}
