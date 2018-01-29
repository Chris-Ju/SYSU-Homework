#include "AgendaUI.hpp"
#include "Storage.hpp"
#include "AgendaService.hpp"
#include "md5.hpp"
#include "Date.hpp"
#include "Meeting.hpp"
#include "my_function.hpp"
#include "User.hpp"
#include <string>
#include <iostream>
#include <list>
#include <iomanip>
#include <conio.h>
#include <regex>



AgendaUI::AgendaUI()
{
	m_instance = new AgendaService;
}

AgendaUI::~AgendaUI()
{
	delete m_instance;
}

void AgendaUI::sycs()
{
	m_instance->quitAgenda();
}

void AgendaUI::OperationLoop()
{
	cout << "----------------------Agenda----------------------" << endl;
	cout << "Action: " << endl;
	cout << "l     - log in Agenda by user name and password" << endl;
	cout << "r     - register an Agenda account" << endl;
	cout << "q     - quit Agenda" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << endl;
	while(1)
	{
		cout << "Agenda :~$";
		string choice;
		cin >> choice;
		cin.clear();
		cin.sync();
		if      (choice == "l") { userLogin();	 break;}
		else if (choice == "r") { userRegister();break;}
		else if (choice == "q") { quit();	     break;}
		else	 cout << "Invalid input" << endl;
	}
}

void AgendaUI::quit()
{
	cout << "[Agenda] Thanks for using me!" << endl;
	m_instance->quitAgenda();
}

void AgendaUI::userLogin()
{
	char name[50]{0}, password[50]{0};
	cout << "[Log in] [username]" << endl;
	cout << "[Log in] ";
	cin.getline(name, 50);
	cin.clear();
	cin.sync();
	cout << "[Log in] [password]" << endl;
	cout << "[Log in] ";
	char ch;
	int i = 0;
	while((ch = getch()) != '\r')
    {
        if(ch != 8)
        {
            password[i] = ch;
            putchar('*');
            i++;
        }
        else
        {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            i--;
        }
    }
    cout << endl;
    cout << "[Log in] ";
	if(m_instance->userLogIn(name, encode.Encode(password)))
	{
		cout << "succeed!" << endl;
		cur_user = name;
		cur_password = password;
		string log = name + string(" logs in successfully!");
		buildLog(log);
		userUI();
	}
	else
	{
		OperationLoop();
	}
}

bool AgendaUI::isNumber(string k)
{
	for(int i = 0; i < k.length(); i++)
	{
		if(!(k[i] >= '0' && k[i] <= '9'))
			return false;
	}
	return true;
}

void AgendaUI::userRegister()
{
	char username[50]{0}, password1[50]{0}, password2[50]{0};
	string email, phone;
	regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
	while(1)
	{
		cout << "[Register] [username] (Length <= 15) (Be able to include space)" << endl;
		cout << "[Register] ";
		cin.getline(username, 50);
		cin.clear();
		cin.sync();
		if(string(username).size() <= 15)
			break;
		else
			cout << "[Register] Length should be lower than 15!" << endl;
	}
	cout << "[Register] [password]" << endl;
	cout << "[Register] ";
	char ch;
	int i = 0;
	while((ch = getch()) != '\r')
    {
        if(ch != 8)
        {
            password1[i] = ch;
            putchar('*');
            i++;
        }
        else
        {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            i--;
        }
    }
    cout << endl;
    cout << "[Register] [Please enter it again]" << endl;
    cout << "[Register] ";
    i = 0;
	while((ch = getch()) != '\r')
    {
        if(ch != 8)
        {
            password2[i] = ch;
            putchar('*');
            i++;
        }
        else
        {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            i--;
        }
    }
    if(string(password1) != string(password2))
    {
    	cout << endl;
    	cout << "Different input!" << endl;
    	OperationLoop();
    	return;
    }
    while(1)
    {
    	cout << endl;
    	cout << "[Register] [email]" << endl;
    	cout << "[Register] ";
    	cin >> email;
    	cin.clear();
    	cin.sync();
    	if(regex_match(email, pattern))
    		break;
    	else
    		cout << "[Register] Please enter right email!" << endl;
    }
	while(1)
	{	
		cout << "[Register] [phone]" << endl;
		cout << "[Register] ";
		cin >> phone;
		cin.clear();
		cin.sync();
		if(string(phone).length() > 11 || !isNumber(phone))
			cout << "[Register] Please enter right number!" << endl;
		else
			break;
	}
	for(i = 0; i < 50; i++)
	{
		if(username[i] == ',' || password1[i] == ',' || email[i] == ',' || phone[i] == ',' || username[i] == '"' || password1[i] == '"' || email[i] == '"' || phone[i] == '"')
		{
			cout << "[Register] Please don't enter ',' or '\"'" << endl; 
			OperationLoop();
			return;
		}
	}
	if(m_instance->userRegister(username, encode.Encode(password1), email, phone))
	{
		cout << "[Register] succeed!" << endl;
		string log = string(username) + " registered successfully!";
		buildLog(log);
		OperationLoop();
	}
	else
	{
		cout << "[Register] This username has been registered" << endl;
		string log = "Someone wants to register a registered name " + string(username);
		buildLog(log);
		OperationLoop();
	}
}

void AgendaUI::userUI()
{
	cout << "----------------------Agenda----------------------" << endl;
	cout << "Action: " << endl;
	cout << "o     - log out Agenda" << endl;
	cout << "dc    - delete Agenda account" << endl;
	cout << "lu    - list all Agenda user" << endl;
	cout << "cm    - create a meeting" << endl;
	cout << "amp   - add meeting participator" << endl;
	cout << "rmp   - remove meeting participator" << endl;
	cout << "rqm   - request to quit meeting" << endl;
	cout << "la    - list all meetings" << endl;
	cout << "las   - list all sponsor meetings" << endl;
	cout << "lap   - list all participator meetings" << endl;
	cout << "qm    - query meeting by title" << endl;
	cout << "qt    - query meeting by time interval" << endl;
	cout << "dm    - delete meeting by title" << endl;
	cout << "da    - delete all meeting" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Agenda@" << cur_user << " :~#";
	string choice;
	cin >> choice;
	cin.clear();
	cin.sync();
	if(choice == "o"  ) 	 OperationLoop();
	else if(choice == "dc" ) deleteUser();
	else if(choice == "lu" ) listAllUser();
	else if(choice == "cm" ) createMeeting();
	else if(choice == "amp") addMeetingParticipator();
	else if(choice == "rmp") removeMeetingParticipator();
	else if(choice == "rqm") quitMeeting();
	else if(choice == "la" ) listAllMeeting();
	else if(choice == "las") listSponsorMeetings();
	else if(choice == "lap") listParticipatorMeetings();
	else if(choice == "qm" ) queryMeetingByTitle();
	else if(choice == "qt" ) queryMeetingByTimeInterval();
	else if(choice == "dm" ) deleteMeetingByTitle();
	else if(choice == "da" ) deleteAllMeeting();
	else   {cout << "Agenda@" << cur_user << " :~# Invalid input" << endl; userUI();}
}

void AgendaUI::deleteUser()
{
	m_instance->deleteUser(cur_user, cur_password);
	cout << endl;
	string log = cur_user + " has been deleted just now"; 
	buildLog(log);
	cout << "Agenda@" << cur_user << " : ~# succeed" << endl;
	OperationLoop();
}

void AgendaUI::listAllUser()
{
	cout << endl;
	list<User> userList = m_instance->listAllUsers();
	cout << left << setw(20) << "[name]" << left << setw(25) << "[email]" << left << "[phone]" << endl;
	for(auto i: userList)
	{
		cout << left << setw(20) << i.getName() << left << setw(25) << i.getEmail() << i.getPhone()  << endl;
	}
	string log = cur_user + " lists all users";
	buildLog(log);
	userUI();
}

void AgendaUI::createMeeting()
{
	cout << endl;
	cout << "[create meeting] [the number of participators]" << endl;
	cout << "[create meeting] ";
	int number;
	cin >> number;
	cin.clear();
	cin.sync();
	while(number <= 0)
	{
		cout << "[create meeting] What? Stupid! Enter again!" << endl;
		cout << "[create meeting] ";
		cin >> number;
		cin.clear();
		cin.sync();

	}
	char str[50]{0};
	vector<string> participators;
	for(int i = 1; i <= number; i++)
	{	
		cout << "[create meeting] [please enter the participator " << i << " ]" << endl;
		cout << "[create meeting] ";
		cin.getline(str, 50);
		cin.clear();
		cin.sync();
		participators.push_back(str);
	}
	char title[50]{0};
	while(1)
	{
		cout << "[create meeting] [title] (Length <= 15) (Be able to include space)" << endl;
		cout << "[create meeting] ";
		cin.getline(title, 50);
		cin.clear();
		cin.sync();
		if(string(title).size() <= 15)
			break;
		else
			cout << "[create meeting] Length should be lower than 15!" << endl;
	}
	string stime, etime;
	while(1)
	{
		cout << "[create meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
		cout << "[create meeting] ";
		cin >> stime >> etime;
		cin.clear();
		cin.sync();
		if(Date::isValid(Date(stime)) && Date::isValid(Date(etime)) && Date(etime) > Date(stime))
			break;
		else
			cout << "[create meeting] Invalid date!" << endl;
	}
	cout << "[create meeting] ";
	if(m_instance->createMeeting(cur_user, title,stime, etime, participators))
	{
		cout << "succeed!" << endl;
		string log = cur_user + " create a meeting named " + string(title);
		buildLog(log);
		userUI();
	}
	else
	{
		userUI();
	}
}

void AgendaUI::addMeetingParticipator()
{
	cout << endl;
	char title[50]{0}, username[50]{0};
	cout << "[add participator] [title]" << endl;
	cout << "[add participator] ";
	cin.getline(title, 50);
	cin.clear();
	cin.sync();
	cout << "[add participator] [participator username]" << endl;
	cout << "[add participator] ";
	cin.getline(username, 50);
	cin.clear();
	cin.sync();
	cout << "[add participator] " << endl;
	if(m_instance->addMeetingParticipator(cur_user, title, username))
	{
		cout << "succeed!" << endl;
		string log = cur_user + " adds " + string(username) + " to " + string(title);
		buildLog(log);
		userUI();
	}
	else
	{
		userUI();
	}
}

void AgendaUI::removeMeetingParticipator()
{
	char title[50]{0}, username[50]{0};
	cout << endl;
	cout << "[remove participator] [meeting title]" << endl;
	cout << "[remove participator] ";
	cin.getline(title, 50);
	cin.clear();
	cin.sync();
	cout << "[remove participator] [participator username]" << endl;
	cout << "[remove participator] ";
	cin.getline(username, 50);
	cin.clear();
	cin.sync();
	if(m_instance->removeMeetingParticipator(cur_user, title, username))
	{
		cout << "succeed!" << endl;
		string log = cur_user + " removes " + string(username) + " from " + string(title);
		buildLog(log);
		userUI();
	}
	else
	{
		userUI();
	}

}

void AgendaUI::quitMeeting()
{
	cout << endl;
	cout << "[quit meeting] [meetint title]" << endl;
	cout << "[quit meeting] ";
	char title[50]{0};
	cin.getline(title, 50);
	cin.clear();
	cin.sync();
	cout << "[quit meeting] ";
	if(m_instance->quitMeeting(cur_user, title))
	{
		cout << "succeed!" << endl;
		string log = cur_user + " quits the meeting " + string(title);
		buildLog(log);
		userUI();
	}
	else
	{
		userUI();
	}

}

void AgendaUI::listAllMeeting()
{
	list<Meeting> meetings = m_instance->listAllMeetings(cur_user);
	cout << endl;
	string log = cur_user + " lists its all meetings";
	buildLog(log);
	cout << "[list all meetings]" << endl;
	if(!meetings.empty())
		cout << left << setw(20) << "[title]" << setw(20) << "[sponsor]" << left << setw(20) << "[start time]" << left << setw(20) << "[end time]" << "[participators]" << endl;
	else
		cout << "Relaxing time! You have no meeting to attend!" << endl;
	for(auto i: meetings)
	{
		cout << left << setw(20) << i.getTitle() << "" << left << setw(20) << i.getSponsor() << "" << left << setw(20) << Date::dateToString(i.getStartDate()) << left << setw(20) << Date::dateToString(i.getEndDate());
		vector<string> tmp = i.getParticipator();
		for(auto j:tmp)
		{
			cout << j << ";";
		}
		cout << endl;
	}
	userUI();
}

void AgendaUI::listSponsorMeetings()
{
	list<Meeting> meetings = m_instance->listAllSponsorMeetings(cur_user);
	string log = cur_user + " lists its meetings as sponsor";
	buildLog(log);
	cout << endl;
	cout << "[list all sponsor meetings]" << endl;
	if(!meetings.empty())
		cout << left << setw(20) << "[title]" << setw(20) << "[sponsor]" << left << setw(20) << "[start time]" << left << setw(20) << "[end time]" << "[participators]" << endl;
	else
		cout << "You are not a sponsor!" << endl;
	for(auto i: meetings)
	{
		cout << left << setw(20) << i.getTitle() << left << setw(20) << i.getSponsor() << Date::dateToString(i.getStartDate()) << left << setw(20) << Date::dateToString(i.getEndDate());
		vector<string> tmp = i.getParticipator();
		for(auto j:tmp)
		{
			cout << j << ";";
		}
		cout << endl;
	}
	userUI();
}

void AgendaUI::listParticipatorMeetings()
{
	list<Meeting> meetings = m_instance->listAllParticipateMeetings(cur_user);
	string log = cur_user + " lists its meetings as participator";
	cout << endl;
	cout << "[list all participate meetings]" << endl;
	if(!meetings.empty())
		cout << left << setw(20) << "[title]" << setw(20) << "[sponsor]" << left << setw(20) << "[start time]" << left << setw(20) << "[end time]" << "[participators]" << endl;
	else
		cout << "You are not a participator!" << endl;
	for(auto i: meetings)
	{
		cout << left << setw(20) << i.getTitle() << "" << left << setw(20) << i.getSponsor() << "" << left << setw(20) << Date::dateToString(i.getStartDate()) << left << setw(20) << Date::dateToString(i.getEndDate());
		vector<string> tmp = i.getParticipator();
		for(auto j:tmp)
		{
			cout << j << ";";
		}
		cout << endl;
	}
	userUI();
}

void AgendaUI::queryMeetingByTitle()
{
	cout << endl;
	cout << "[query meeting] [title]" << endl;
	cout << "[query meeting] ";
	char title[50]{0};
	cin.getline(title, 50);
	cin.clear();
	cin.sync();
	list<Meeting> meetings = m_instance->meetingQuery(cur_user, title);
	if(!meetings.empty())
		cout << left << setw(20) << "[title]" << setw(20) << "[sponsor]" << left << setw(20) << "[start time]" << left << setw(20) << "[end time]" << "[participators]" << endl;
	else
		cout << "You needn't attend the meetings!" << endl;
	for(auto i: meetings)
	{
		cout << left << setw(20) << i.getTitle() << left << setw(20) << i.getSponsor() << left << setw(20) << Date::dateToString(i.getStartDate()) << left << setw(20) << Date::dateToString(i.getEndDate());
		vector<string> tmp = i.getParticipator();
		for(auto j:tmp)
		{
			cout << j << ";";
		}
		cout << endl;
	}
	string log = cur_user + " query a meeting named " + string(title);
	buildLog(log);
	userUI();
}

void AgendaUI::queryMeetingByTimeInterval()
{
	string stime, etime;
	while(1)
	{
		cout << endl;
		cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
		cout << "[query meeting] ";
		cin >> stime >> etime;
		cin.clear();
		cin.sync();
		Date st(stime), et(etime);
		if(!(Date::isValid(st) && Date::isValid(et) && st <= et))
		{
			cout << "Invalid input!" << endl;
		}
		else
			break;
	}
	list<Meeting> meetings = m_instance->meetingQuery(cur_user, stime, etime);
	if(!meetings.empty())
		cout << left << setw(20) << "[title]" << setw(20) << "[sponsor]" << left << setw(20) << "[start time]" << left << setw(20) << "[end time]" << "[participators]" << endl;
	else
		cout << "Quickly make a plan! You have no meeting during the time!" << endl;
	for(auto i: meetings)
	{
		cout << left << setw(20) << i.getTitle() << left << setw(20) << i.getSponsor() << left << setw(20) << Date::dateToString(i.getStartDate()) << left << setw(20) << Date::dateToString(i.getEndDate());
		vector<string> tmp = i.getParticipator();
		for(auto j:tmp)
		{
			cout << j << ";";
		}
		cout << endl;
	}
	string log = cur_user + " query during time " + " if it has meetings";
	buildLog(log);
	userUI();
}

void AgendaUI::deleteMeetingByTitle()
{
	cout << endl;
	cout << "[delete meeting] [title]" << endl;
	cout << "[delete meeting] ";
	char title[50]{0};
	cin.getline(title, 50);
	cin.clear();
	cin.sync();
	cout << "[delete meeting] ";
	if(m_instance->deleteMeeting(cur_user, title))
	{
		cout << "succeed!" << endl;
		string log = cur_user + " deletes meeting named " + string(title); 
		buildLog(log);
		userUI();
	}
	else
	{
		userUI();
	}

}
void AgendaUI::deleteAllMeeting()
{
	cout << endl;
	cout << "[delete all meetings] " << endl;
	if(m_instance->deleteAllMeetings(cur_user))
		cout << "succeed!" << endl;
	else
		cout << "You are not a sponsor!" << endl;
	string log = cur_user + " trys to delete all his meetings as sponsor";
	buildLog(log);
	userUI();
}


