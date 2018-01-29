#include "AgendaUI.hpp"
#include <Windows.h>
#include <signal.h>
#include <iostream>

AgendaUI* aui;

using namespace std;
void cs(int n)
{
	if(n == SIGINT)
	{
		aui->sycs();
		exit(0);
	}
}

int main()
{
 	aui = new AgendaUI;
	signal(SIGINT, cs);
	aui->OperationLoop();
	return 0;
}
