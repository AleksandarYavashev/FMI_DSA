#pragma once
#include "Column.h"

class ColumnDouble : public Column
{
private:
	double* arr;
private:
	double convertToDouble(const char*);
	void resize();
	void resetLocation() { currLocation = 0; }

	ColumnDouble(const ColumnDouble&) {}
	ColumnDouble& operator=(const ColumnDouble&) {}

public:
	ColumnDouble(int _capacity = 1) :
		Column(_capacity)
	{
		arr = new double[_capacity];
		type = ColumnType::DOUBLE;
	}

	ColumnDouble(int _size, double* arr);
	virtual ~ColumnDouble() { delete[] arr; }

	virtual void serialize(std::ofstream&) const;
	virtual void deSerialize(std::ifstream&);

	virtual void addElement(const char*);
	virtual void deleteElement(int);
	virtual void changeElement(int, const char*);
	virtual const char* getElement(int rowIndex) const;

	void startFind();
	virtual	int findNext(const char*);

	virtual void printType() const;

public:
	int getSize() const { return capacity; }
};