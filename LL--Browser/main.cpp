// Aleksandar Yavashev fn45216
// SDP 1st HW


#include <iostream>
#include "LList.h"
#include "Tab.h"

const int CMD_SIZE = 16;
const int URL_SIZE = 128;


void callCommand(char* str, LList<Tab>::Iterator it);
void go(LList<Tab>::Iterator it);
void back(LList<Tab>::Iterator it);
void forward(LList<Tab>::Iterator it);
void insert(LList<Tab>::Iterator it);
void remove(LList<Tab>::Iterator it);
void print(LList<Tab>::Iterator it);

int main()
{

	LList<Tab> browser;
	LList<Tab>::Iterator iter=browser.getIterFront();

	Tab* defaultTab = new Tab("about:blank");
	browser.pushFront(*defaultTab);

	char cmd[CMD_SIZE];

	while (std::cin >> cmd)
		callCommand(cmd,iter);

	system("pause");
	return 0;
}

void go(LList<Tab>::Iterator it)
{
	char URL[URL_SIZE];
	std::cin >> URL;
	it->changeName(URL);
}

void back(LList<Tab>::Iterator it)
{
	--it;
}

void forward(LList<Tab>::Iterator it)
{
	++it;
}

void insert(LList<Tab>::Iterator it)
{
	char URL[URL_SIZE];
	std::cin >> URL;
	Tab* tab = new Tab(URL);
	it.insert(*tab);
}

void remove(LList<Tab>::Iterator it)
{
	it.erease();
}

void print(LList<Tab>::Iterator it)
{
	LList<Tab>::Iterator iterator;
	LList<Tab>::Iterator nullIter(nullptr);

	while (iterator!=nullIter)
	{
		if (iterator == it)
			std::cout << '>';

			iterator->print();
			++iterator;
	}
}

void callCommand(const char* command, LList<Tab>::Iterator it)
{	
	if (strcmp(command, "GO") == 0)
	{
		go(it);
	}
	else if (strcmp(command, "BACK") == 0)
	{
		back(it);
	}
	else if (strcmp(command, "FORWARD") == 0)
	{
		forward(it);
	}
	else if (strcmp(command, "INSERT") == 0)
	{
		insert(it);
	}
	else if (strcmp(command, "REMOVE") == 0)
	{
		remove(it);
	}
	else if (strcmp(command, "PRINT") == 0)
	{
		print(it);
	}
	else
	{
		std::cout << "Wrong command input.\n";
	}
}
