#include "AgendaService.hpp"
#include "my_function.hpp"
#include "User.hpp"
#include "Date.hpp"
#include "Meeting.hpp"
#include "Storage.hpp"
#include <list>
#include <string>
#include <iostream>
#include <set>
#include <exception>
#include <string>

using std::cout;
using std::endl;

AgendaService::AgendaService()
{
	startAgenda();
}

AgendaService::~AgendaService()
{
	quitAgenda();
}

bool AgendaService::userLogIn(const std::string &userName, const std::string &password)
{
	std::list<User> tmp = m_storage->queryUser([userName, password](const User& k){ if(k.getName() == userName) return true; return false;});
	try
	{
		if(tmp.empty())
		{
			throw "User doesn't exit!";
		}
		else if(tmp.front().getPassword() != password)
		{
			throw "password error!";
		}
		return true;
	}
	catch(const char* k)
	{
		std::string log = userName + " wants to log in, but " + k;
		buildLog(log);
		std::cout << k << std::endl;
		return false;
	}
}

bool AgendaService::userRegister(const std::string &userName, const std::string &password, const std::string &email, const std::string &phone)
{
	std::list<User> tmp = m_storage->queryUser([userName](const User& k){ return k.getName() == userName;});
	if(!tmp.empty())
		return false;
	m_storage->createUser(User(userName, password, email, phone));
	return true;
}

bool AgendaService::deleteUser(const std::string &userName, const std::string &password)
{
	int count = m_storage->deleteUser([userName, password](const User& k)
		{ if(k.getName() == userName && k.getPassword() == password) return true; return false;});
	if(count != 0)
	{
		m_storage->deleteMeeting([userName](const Meeting& k)
			{ return k.getSponsor() == userName;});
		m_storage->deleteMeeting([userName](const Meeting& k)
			{ if(k.isParticipator(userName) && k.getParticipator().size() == 1)
				return true;
			return false;});
		m_storage->updateMeeting([userName](const Meeting& k)
			{ if(k.isParticipator(userName) && k.getParticipator().size() > 1)
				return true;
			return false;}, [userName](Meeting& k) { k.removeParticipator(userName);});
		return true;
	}
	else
		return false;
}

std::list<User> AgendaService::listAllUsers(void) const
{
	return m_storage->queryUser([](const User& k){return true;});
}

bool AgendaService::createMeeting(const std::string &userName, const std::string &title, const std::string &startDate, const std::string &endDate, const std::vector<std::string> &participator)
{
	try
	{
		if(!(Date::isValid(Date(startDate)) && Date::isValid(Date(endDate))))
			return false;
		if(startDate >= endDate)
			return false;
		std::list<User> _tmp_ = m_storage->queryUser([userName](const User& k){return k.getName() == userName;});
		if(_tmp_.empty())
			return false;
		std::list<Meeting> _tmp = m_storage->queryMeeting([userName, title, endDate, startDate](const Meeting& k)
		{
			if(k.getTitle() == title)
				throw "The meeting has existed!";
			if((k.getSponsor() == userName || k.isParticipator(userName)) && !(Date::stringToDate(startDate) >= k.getEndDate() || Date::stringToDate(endDate) <= k.getStartDate()))
				throw "You have a meeting during the time!";
			return false;
		});
		if(!_tmp.empty())
			return false;
		std::set<std::string> name;
		for(auto i:participator)
		{
			if(userName == i)
				return false;
			name.insert(i);
			std::list<User> tmp = m_storage->queryUser([i](const User& k){return i == k.getName();});
			if(tmp.empty())
			{
				std::string reason = i + " doesn't exist!";
				throw reason;
			}
			std::list<Meeting> tmp_ = listAllMeetings(i);
			for(auto j:tmp_)
			{
				if(!(Date(startDate) >= j.getEndDate() || Date(endDate) <= j.getStartDate()))
				{
					std::string reason = i + " has other meeting during the time!";
					throw reason;
				}
			}
		}
		if(name.size() != participator.size())
			throw "Stupid? You add some same persons in it?";
		m_storage->createMeeting(Meeting(userName, participator, startDate, endDate, title));
		return true;
	}
	catch(std::string k)
	{
		std::string log = userName + " wants to create a meeting named " + title + ", but " + k;
		buildLog(log);
		std::cout << k << std::endl;
		return false;
	}
}

bool AgendaService::addMeetingParticipator(const std::string &userName, const std::string &title, const std::string &participator)
{
	try
	{
		std::list<User> _tmp = m_storage->queryUser([participator](const User& k){return participator == k.getName();});
		if(_tmp.empty())
			throw "User doesn't exist!";

		std::list<User> __tmp = m_storage->queryUser([userName](const User& k){return userName == k.getName();});
		if(__tmp.empty())
			throw "User doesn't exist!";

		std::list<Meeting> tmp = m_storage->queryMeeting([userName, title, participator](const Meeting& k){
			if(k.getTitle() == title && k.getSponsor() == userName)
				return true;
			return false;
		});
		if(tmp.empty())
			throw "Meeting doesn't exist!";

		if(tmp.front().isParticipator(participator))
		{
			throw "The user has been the meeting's participator!";
			return false;		}
		std::list<Meeting> tmp_ = listAllMeetings(participator);
		for(auto p: tmp_)
		{
			if(!((tmp.front()).getStartDate() >= p.getEndDate() || (tmp.front()).getEndDate() <= p.getStartDate()))
				throw "The participator has other meeting during the time!";
		}
		m_storage->updateMeeting(([userName, title, participator](const Meeting& k){
		if(k.getTitle() == title && k.getSponsor() == userName && !k.isParticipator(participator))
			return true;
		return false;
		}), ([participator](Meeting &k){ k.addParticipator(participator);}));
		return true;
	}
	catch(const char* k)
	{
		std::string log = userName + " wants to add " + participator + " to " + title + ", but " + k;
		buildLog(log);
		std::cout << k << endl;
		return false;
	}
}

bool AgendaService::removeMeetingParticipator(const std::string &userName, const std::string &title, const std::string &participator)
{
	try
	{
		std::list<Meeting> tmp = m_storage->queryMeeting([userName, title, participator](const Meeting& k){
		if(k.getTitle() == title && k.getSponsor() == userName)
			return true;
		return false;
		});
		std::list<User> _tmp = m_storage->queryUser([participator](const User& k){return participator == k.getName();});
		if(_tmp.empty())
			throw "User doesn't exist!";
		if(tmp.empty())
			throw "Meeting doesn't exist!";
		if(!tmp.front().isParticipator(participator))
			throw "The user isn't the meeting's participator!";
		if((tmp.front()).getParticipator().size() == 1)
		{
			m_storage->deleteMeeting([userName, title, participator](const Meeting& k){
			if(k.getTitle() == title && k.getSponsor() == userName && k.isParticipator(participator) )
				return true;
			return false;
		});
			return true;
		}
		else
		{
			m_storage->updateMeeting(([userName, title, participator](const Meeting& k){
			if(k.getTitle() == title && k.getSponsor() == userName && k.isParticipator(participator))
				return true;
			return false;
		}), ([participator](Meeting &k){ k.removeParticipator(participator);}));
			return true;
		}
	}
	catch(const char* k)
	{
		std::string log = userName + " wants to remove " + participator + " from " + title + ", but " + k;
		buildLog(log);
		std::cout << k << std::endl;
		return false;
	}
}

bool AgendaService::quitMeeting(const std::string &userName, const std::string &title)
{
	try
	{
		std::list<User> _tmp = m_storage->queryUser([userName](const User& k){return userName == k.getName();});
		if(_tmp.empty())
			throw "User doesn't exist!";
		std::list<Meeting> tmp = m_storage->queryMeeting([userName, title](const Meeting& k){
			if(k.getTitle() == title)
				return true;
			return false;
		});
		if(tmp.empty())
			throw "Meeting doesn't exist!";
		if(!tmp.front().isParticipator(userName))
			throw "You're not the meeting's participator!";
		if((tmp.front()).getParticipator().size() == 1)
		{
			m_storage->deleteMeeting([userName, title](const Meeting& k){
			if(k.getTitle() == title && k.isParticipator(userName))
				return true;
			return false;
		});
			return true;
		}
		else
		{
			m_storage->updateMeeting(([userName, title](const Meeting& k){
			if(k.getTitle() == title && k.isParticipator(userName))
				return true;
			return false;
		}), ([userName](Meeting &k){ k.removeParticipator(userName);}));
			return true;
		}
	}
	catch(const char* k)
	{
		std::string log = userName + " wants to quit meeting named " + title + ", but " + k;
		buildLog(log);
		std::cout << k << std::endl;
		return false;
	}
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName, const std::string &title) const
{
	return m_storage->queryMeeting([userName, title](const Meeting& k){ if(k.getTitle() == title && (k.getSponsor() == userName || k.isParticipator(userName))) return true; return false;});
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName, const std::string &startDate, const std::string &endDate) const
{
	std::list<Meeting> k;
	if(!Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate)))
		return k;
	if(Date::stringToDate(startDate) > Date::stringToDate(endDate))
		return k;
	return m_storage->queryMeeting([userName, startDate, endDate](const Meeting& k){
		if(k.getSponsor() == userName || k.isParticipator(userName))
		{
			if(!(Date::stringToDate(startDate) >= k.getEndDate() || Date::stringToDate(endDate) <= k.getStartDate()))
				return true;
		}
		return false;
	});
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const
{
	return m_storage->queryMeeting([userName](const Meeting& k){  if(k.isParticipator(userName) || k.getSponsor() == userName) return true; return false;});
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const
{
	return m_storage->queryMeeting([userName](const Meeting& k){ return k.getSponsor() == userName;});
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string &userName) const
{
	return m_storage->queryMeeting([userName](const Meeting& k){ return k.isParticipator(userName);});
}


bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title)
{
	try
	{
		std::list<Meeting> tmp = m_storage->queryMeeting(([title](const Meeting& k){if(k.getTitle() == title) return true; return false;}));
		if(tmp.empty())
			throw "Meeting doesn't exist";
		if(tmp.front().getSponsor() != userName)
			throw "You are not the sponsor of the meeting!";
		else
		{
			m_storage->deleteMeeting(([title](const Meeting& k){if(k.getTitle() == title) return true; return false;}));
			return true;
		}
	}
	catch(const char* k)
	{
		std::string log = userName + " wants to delete meeting named " + title + ", but " + k;
		buildLog(log);
		std::cout << k << std::endl;
		return false;
	}
}

bool AgendaService::deleteAllMeetings(const std::string &userName)
{
	int count = m_storage->deleteMeeting([userName](const Meeting& k){ return k.getSponsor() == userName; });
	if(count == 0)
		return false;
	return true;
}

void AgendaService::startAgenda(void)
{
	m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void)
{
	m_storage->sync();
}


