#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Constants.h"

static const int RESIZE = 8;
static const int INVALID_INDEX = -1;

class Column
{
protected:
	ColumnType type;
	int size;
	int capacity;
	int currLocation;

public:
	Column(int cap = 0, int siz = 0) : capacity(cap), size(siz) {}

	virtual ~Column() {}

public:
	int getNumberRows() const { return size; }

	virtual void serialize(std::ofstream&) const{}
	virtual void deSerialize(std::ifstream&) {}
	
	
	virtual void addElement(const char*) = 0;

	virtual const char* getElement(int rowIndex) const = 0;

	virtual void deleteElement(int) = 0;

	void startFind() { currLocation = 0; }
	virtual int findNext(const char*) = 0;

	virtual void changeElement(int, const char*) = 0;
	virtual void printType() const = 0;

private:
	DISABLE_COPY(Column);
};