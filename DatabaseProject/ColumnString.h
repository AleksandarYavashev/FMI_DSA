#pragma once
#include "Column.h"

class ColumnString : public Column
{
private:
	char** str;

private:
	void resize();

public:
	ColumnString(int capacity = 1) :Column(capacity)
	{
		str = new char*[capacity];
		type = ColumnType::STRING;
	}

	virtual ~ColumnString();

	virtual void serialize(std::ofstream&) const;
	virtual void deSerialize(std::ifstream&);

	virtual void addElement(const char*);

	virtual const char* getElement(int) const;

	virtual void deleteElement(int);
	virtual void changeElement(int, const char*);

	void startFind();
	virtual	int findNext(const char*);

	virtual void printType() const;

};