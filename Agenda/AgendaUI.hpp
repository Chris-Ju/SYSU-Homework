#ifndef AGENDA_UI
#define AGENDA_UI
#include "Storage.hpp"
#include "my_function.hpp"
#include "AgendaService.hpp"
#include "md5.hpp"
#include "Date.hpp"
#include "Meeting.hpp"
#include "User.hpp"
#include <string>
#include <iostream>
#include <list>
#include <iomanip>
#include <conio.h>
#include <regex>

using namespace std;

class AgendaUI
{
private:
	AgendaService* m_instance = nullptr;
	string cur_user;
	string cur_password;
	Md5Encode encode;

public:
	AgendaUI();
	~AgendaUI();
	void userLogin();
	void userRegister();
	void quit();
	void OperationLoop();
	void userUI();

	void deleteUser();
	void listAllUser();
	void createMeeting();
	void addMeetingParticipator();
	void removeMeetingParticipator();
	void quitMeeting();
	void listAllMeeting();
	void listSponsorMeetings();
	void listParticipatorMeetings();
	void queryMeetingByTitle();
	void queryMeetingByTimeInterval();
	void deleteMeetingByTitle();
	void deleteAllMeeting();
	void sycs();
	bool isNumber(string);
};


#endif