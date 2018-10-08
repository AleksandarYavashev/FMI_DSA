#pragma once
#include "Column.h"

class ColumnInt : public Column
{
private:
	int* arr;
private:
	int convertToInt(const char*);
	void resize();

	ColumnInt(const ColumnInt&) {}
	ColumnInt& operator=(const ColumnInt&) {}

public:
	ColumnInt(int _capacity = 1) :
		Column(_capacity) 
	{ 
		arr = new int[_capacity];
		type = ColumnType::INT;
	}

	ColumnInt(int _size, int* arr);
	virtual ~ColumnInt() { delete[] arr; }

	virtual void serialize(std::ofstream&) const;
	virtual void deSerialize(std::ifstream&);

	virtual void addElement(const char*);
	
	virtual const char* getElement(int rowIndex) const;

	virtual void deleteElement(int);
	virtual void changeElement(int, const char*);

	void startFind();
	virtual	int findNext(const char*);
	
	virtual void printType() const;

public:
	int getSize() const { return capacity; }
};