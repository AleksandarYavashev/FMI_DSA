#ifndef _TAB_HEADER_INCLUDED_
#define _TAB_HEADER_INCLUDED_

#include <time.h>
#include <string.h>
#include <iostream>
class Tab
{
private:
	char* name;
	time_t timer;
public:
	Tab()
	{
		name = nullptr;
		timer = time(NULL);
	}
	Tab(char* str)
	{
		name = new char[strlen(str) + 1];
		strcpy(name, str);
		timer = time(NULL);
	}

	~Tab()
	{
		if (name != nullptr)
		{
			delete[] name;
		}
	}

public:
	void print()
	{
		std::cout << name << ' ' << timer << '\n';
	}

	void changeName(const char* str)
	{
		delete[] name;
		name = new char[strlen(str) + 1];
		strcpy(name, str);
		timer = time(NULL);
	}
};

#endif //  _TAB_HEADER_INCLUDED_