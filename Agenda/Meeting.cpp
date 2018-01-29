#include "Meeting.hpp"
#include <string>
#include <vector>
#include <algorithm>
using std::vector;
using std::string;
using std::find;

Meeting::Meeting(const std::string &t_sponsor,
          const std::vector<std::string> &t_participator,
          const Date &t_startTime, const Date &t_endTime,
          const std::string &t_title)
{
	m_sponsor = t_sponsor;
	m_startDate = t_startTime;
	m_endDate = t_endTime;
	m_title = t_title;
	m_participators.assign(t_participator.begin(), t_participator.end());
}

Meeting::Meeting(const Meeting &t_meeting)
{
	m_sponsor = t_meeting.m_sponsor;
	m_startDate = t_meeting.m_startDate;
	m_endDate = t_meeting.m_endDate;
	m_title = t_meeting.m_title;
	m_participators.assign(t_meeting.m_participators.begin(), t_meeting.m_participators.end());
}

string Meeting::getSponsor(void) const
{
	return m_sponsor;
}

void Meeting::setSponsor(const string &t_sponsor)
{
	m_sponsor = t_sponsor;
}

vector<std::string> Meeting::getParticipator(void) const
{
	return m_participators;
}

void Meeting::setParticipator(const vector<string> &t_participators)
{
	m_participators.assign(t_participators.begin(), t_participators.end());
}

void Meeting::addParticipator(const string &t_participator)
{
	if(isParticipator(t_participator))
		return;
	m_participators.push_back(t_participator);
}

void Meeting::removeParticipator(const string &t_participator)
{
	m_participators.erase(remove(m_participators.begin(), m_participators.end(), t_participator), m_participators.end());
}

Date Meeting::getStartDate(void) const
{
	return m_startDate;
}

void Meeting::setStartDate(const Date &t_startTime)
{
	m_startDate = t_startTime;
}

Date Meeting::getEndDate() const
{
	return m_endDate;
}

void Meeting::setEndDate(const Date &t_endTime)
{
	m_endDate = t_endTime;
}

string Meeting::getTitle(void) const
{
	return m_title;
}

void Meeting::setTitle(const string &t_title)
{
	m_title = t_title;
}

bool Meeting::isParticipator(const string &t_username) const
{
	auto item = find(m_participators.begin(), m_participators.end(), t_username);
	if(item != m_participators.end())
		return true;
	return false;
}
