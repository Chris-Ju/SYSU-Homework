#include "user.hpp"
#include "userController.hpp"
#include <cstring>
#include <sstream>

using namespace Alipay;

int userController::getUserIndex(const char* username) const
{
    for(int i = 0; i < usercount; i++)
        if(strcmp(users[i]->getUsername(), username) == 0)
            return i;
    return -1;
}

userController::userController(double interst_rate)
{
    this->interest_rate = interst_rate;
    usercount = 0;
}

userController::~userController()
{
    for(int i = 0; i < usercount; i++)
    {
        delete users[i];
        users[i] = NULL;
    }
}

bool userController::createUser(const char* username, const char* password)
{
    if(strlen(username) > 20 || strlen(username) < 6 || strlen(password) >20 || strlen(password) < 8)
        return false;
    if(usercount == MAX_USER)
        return false;
    users[usercount] = new user(username, password);
    usercount++;
    return true;
}

bool userController::deposite(const char* username, double amount)
{
    int n = getUserIndex(username);
    if(n == -1)
        return false;
    return users[n]->deposite(amount);
}

bool userController::withdraw(const char* username, double amount)
{
    int n = getUserIndex(username);
    if(n == -1)
        return false;
    return users[n]->withdraw(amount);
}

int userController::getUserCount(void) const
{
    return usercount;
}


std::string userController::getUserInfoByName(const char* username) const
{
    int n = getUserIndex(username);
    std::string a = users[n]->getUsername();
    std::string b = "*********\n";
    std::string c;
    double t = users[n]->getBalance();
    std::stringstream d;
    d << t;
    d >> c;
    std::string goal = "username:" + a + "\n" + "password:" + b + "balance:" + c;
    return goal;
}

bool userController::removeUserByUsername(const char* username)
{
    int n = getUserIndex(username);
    if(n == -1)
        return false;
    delete users[n];
    users[n] = users[usercount - 1];
    users[usercount - 1] = NULL;
    usercount--;
    return true;
}

bool userController::setInterest(double interest)
{
    if(interest <= 0)
        return false;
    interest_rate = interest;
    return true;
}

void userController::payInterest()
{
    double n;
    for(int i = 0; i < usercount; i++)
    {
        n = users[i]->getBalance() * interest_rate;
        users[i]->deposite(n);
    }  
}


