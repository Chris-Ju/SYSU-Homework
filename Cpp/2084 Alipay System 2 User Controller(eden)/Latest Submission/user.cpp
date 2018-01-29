 #include "user.hpp"
#include <cstring>

using namespace Alipay;

user::user(const char* username, const char* password)
{
    balance = 0;
    strncpy(this->username, username, strlen(username) + 1);
    strncpy(this->password, password,strlen(password) + 1);
}

user::~user()
{
}

const char* user::getUsername() const
{
    return username;
}

const char* user::getPassword() const
{
    return password;
}

const void user::setUsername(const char* username)
{
    strcpy(this->username, username);
}

const void user::setPassword(const char* password)
{
    strcpy(this->password, password);
}

double user::getBalance()
{
    return balance;
}

bool user::withdraw(double amount)
{
    if(amount > balance || amount < 0)
        return false;
    balance -= amount;
    if(balance < 1e-6)
        balance = 0;
    return true;
}

bool user::deposite(double amount)
{
    if(amount < 0)
        return false;
    if(amount > 1e-6)
        balance += amount;
    return true;
}




