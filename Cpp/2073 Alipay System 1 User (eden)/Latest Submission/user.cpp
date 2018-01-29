 #include "user.hpp"
#include <string>
#include <cstring>


inline bool alipay::User::verifyPasswordFormat(const std::string & password)
{
	int i;
	if(password.length() > 20 || password.length() < 8)
		return false;
	for(i = 0; i < password.length(); i++)
		if(!(password[i] <= 'z' && password[i] >= 'a' || password[i] <= 'Z' && password[i] >= 'A' || password[i] <= '9' && password[i] >= '0'))
			return false;
	return true;
}

inline bool alipay::User::verifyUsernameFormat(const std::string & username)
{
	int i;
	if(username.length() > 20 || username.length() < 6)
		return false;
	for(i = 0; i < username.length(); i++)
		if(!(username[i] <= 'z' && username[i] >= 'a' || username[i] <= 'Z' && username[i] >= 'A' || username[i] <= '9' && username[i] >= '0'))
			return false;
	return true;
}

inline bool alipay::User::verifyPhoneFormat(const std::string & phone)
{
	int i;
	if(phone.length() != 13)
		return false;
	for(i = 0; i < phone.length(); i++)
		if(!(phone[i] <= '9' && phone[i] >= '0' ))
			return false;
	return true;
}

bool alipay::User::setUsername(const char * username)
{
	this->username = username;
	return User::verifyUsernameFormat(this->username);
}

bool alipay::User::setPassword(const char *new_password, const char *old_password)
{

	std::string node0 = new_password;
	std::string node1 = old_password;
	if(verifyPasswordFormat(node0))
	{
		this->password = node0;
		return true;
	}
	else
	{
		this->password = node1;
		return false;
	}
}

bool alipay::User::setPhone(const char *new_phone)
{
	this->phone = new_phone;
	return User::verifyPhoneFormat(this->phone);
}

bool alipay::User::setGender(Gender::Gender gender)
{
	this->gender = gender;
	return true;
}

std::string alipay::User::getUsername()
{
	return User::username;
}
std::string alipay::User::getPhone()
{
	return User::phone;
}

alipay::Gender::Gender alipay::User::getGender()
{
	return User::gender;
}

long long int alipay::User::getMoneyAmount(const char *password)
{
	std::string node = password;
	if(node == this->password)
		return this->balance;
	else
		return -1 ;
}
bool alipay::User::deposit(long long int amount)
{
	if(amount < 0)
   return false;
 this->balance +=amount;
	return true;
}

bool alipay::User::withdraw(long long int amount, const char *password)
{
	if(amount < 0 || amount > this->balance)
   return false;
 char node[20] = {0};
	int i;
	for(i = 0; i < this->password.length(); i++)
		node[i] = this->password[i];
	
	if(!strcmp(node, password))
	{
		this->balance -= amount;
		return true;
	}
	else
		return false;
}