#include "Path.hpp"
#include "Meeting.hpp"
#include "Date.hpp"
#include "User.hpp"
#include "Storage.hpp"
#include <functional>
#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;

std::shared_ptr<Storage> Storage::m_instance = NULL;

Storage::Storage()
{
 m_dirty = false;
 readFromFile();
}


vector<string> getPartner(const string& str)
{
 vector<string> partner;
 if(str.length() == 0)
 	return partner;
 int i,last = 0;
 string tmp;
 for(i = 0; i < str.length(); i++)
 {
    if(str[i] == '&')
    {
     tmp = str.substr(last, i - last);
     last = i + 1;
     partner.push_back(tmp);

    }
 }
 tmp = str.substr(last, i - last);
 partner.push_back(tmp);
 return partner;
}

bool Storage::readFromFile(void)
{
 m_meetingList.clear();
 m_userList.clear();
 string bri;
 ifstream userfile(Path::userPath);
 if(!userfile)
 	return false;
 string data1, data2, data3, data4;
 int k;
 int l[3];
 while(getline(userfile, bri))
 {
    if(bri.length() == 0)
    	continue;
    k = 0;
    for(int i = 0; i < bri.length(); i++)
    {
    	if(bri[i] == ',')
    		l[k++] = i;
    }
    data1 = bri.substr(1, l[0] - 2);
    data2 = bri.substr(l[0] + 2, l[1] - l[0] - 3);
    data3 = bri.substr(l[1] + 2, l[2] - l[1] - 3);
    data4 = bri.substr(l[2] + 2, bri.length() - l[2] - 3);
    User tmp(data1, data2, data3, data4);
    m_userList.push_back(tmp);
 }
 userfile.close();

 ifstream meetingfile(Path::meetingPath);
 if(!meetingfile)
    return false;
 string p;
 int last, times;
 while(getline(meetingfile,bri))
 {
    if(bri.length() == 0)
    	continue;
    Meeting a;
    last = 1;
    times = 0;
    for(int i = 0; i < bri.length(); i++)
    {
     if(bri[i] == ',')
     {
    p = bri.substr(last, i - last - 1);
    last = i + 2;
    switch(times)
    {
     case 0:a.setSponsor(p);break;
     case 1:a.setParticipator(getPartner(p));break;
     case 2:a.setStartDate(Date::stringToDate(p));break;
     case 3:a.setEndDate(Date::stringToDate(p));break;
     default:break;
    }
    times++;
     }
    }
    p = bri.substr(last, bri.length() - last - 1);
    a.setTitle(p);
    m_meetingList.push_back(a);
 }
 meetingfile.close();
 return true;
}

bool Storage::writeToFile(void)
{
 ofstream userfile(Path::userPath, ios::out);
 if(!userfile)
    return false;
 for(auto i: m_userList)
    userfile << "\"" << i.getName()<< "\",\"" 
	<< i.getPassword() << "\",\"" << i.getEmail() << "\",\"" << i.getPhone() << "\"\n";
 userfile.close();
 ofstream meetingfile(Path::meetingPath, ios::out);
 if(!meetingfile)
 	return false;
 for(auto i: m_meetingList)
 {
    
    meetingfile << "\"" << i.getSponsor() << "\",\"";
    vector<string> v = i.getParticipator();
    if(!v.empty())
    {
    	vector<string>::iterator item = v.begin();
    	meetingfile << *item;
    	item++;
    	while(item != v.end())
    	{
     		meetingfile << "&" << *item;
    item++;
    	}
    }
    meetingfile << "\",\"" << Date::dateToString(i.getStartDate()) << "\",\"" << Date::dateToString(i.getEndDate()) 
    << "\",\"" << i.getTitle() << "\"\n";
    }
 meetingfile.close();
 m_dirty = false;
 return true;
}

std::shared_ptr<Storage> Storage::getInstance(void)
{
 if(m_instance == NULL)
    m_instance = std::shared_ptr<Storage>(new Storage);
 return m_instance;
}

Storage::~Storage()
{
 writeToFile();
 m_instance = NULL;
}

void Storage::createUser(const User &t_user)
{
 m_userList.push_back(t_user);
 m_dirty = true;
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const
{
 std::list<User> user;
 for(auto i: m_userList)
 {
    if(filter(i))
     user.push_back(i);
 }
 return user;
}

 
int Storage::updateUser(std::function<bool(const User &)> filter,
     std::function<void(User &)> switcher)
{
 int count = 0;
 for(auto &i : m_userList)
 {
    if(filter(i))
    { 
     switcher(i);
     m_dirty = true;
     count++;
    }
 }
 return count;
}

int Storage::deleteUser(std::function<bool(const User &)> filter)
{
 int count = 0;
 for(std::list<User>::iterator i = m_userList.begin(); i != m_userList.end();)
 {
    if(filter(*i))
    { 
     i = m_userList.erase(i);
     m_dirty = true;
     count++;
    }
    else i++;
 }
 return count;
}

void Storage::createMeeting(const Meeting &t_meeting)
{
 m_meetingList.push_back(t_meeting);
 m_dirty = true;
}
    
std::list<Meeting> Storage::queryMeeting(
    std::function<bool(const Meeting &)> filter) const
{
 std::list<Meeting> meeting;
 for(auto i: m_meetingList)
 {
    if(filter(i))
     meeting.push_back(i);
 }
 return meeting;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
    std::function<void(Meeting &)> switcher)
{
 int count = 0;
 for(auto &i: m_meetingList)
 {
    if(filter(i))
    { 
     switcher(i);
     m_dirty = true;
     count++;
    }
 }
 return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter)
{
 int count = 0;
 for(std::list<Meeting>::iterator i = m_meetingList.begin(); i != m_meetingList.end();)
 {
    if(filter(*i))
    { 
     i = m_meetingList.erase(i);
     m_dirty = true;
     count++;
    }
    else i++;
 }
 return count;
}


bool Storage::sync()
{
    return writeToFile();
}