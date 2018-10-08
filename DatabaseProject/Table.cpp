#include "Table.h"
#include <cassert>
#include <algorithm>

Column* Table::createColumn(ColumnType type)
{
	switch (type)
	{
	case ColumnType::INT:
		return new ColumnInt; 

	case ColumnType::DOUBLE:
		return new ColumnDouble;

	case ColumnType::STRING:
		return new ColumnString;
	}

	assert(false);
	return NULL;
}

Table::Table(const char * tableName) :
	size(0),
	capacity(0),
	column(nullptr)
{
	name = new char[strlen(tableName)+1];
	strcpy(name, tableName);
}

Table::~Table()
{
	delete[] name;
	delete[] column;

	name = nullptr;
	column = nullptr;
}
/*
Table& Table::operator=(const Table& src)
{
	name = new char[strlen(src.name) + 1];
	strcpy(name, src.name);
	column = new Column*[src.size];
	for (int i = 0; i < size; ++i)
		column[i] = src.column[i];
	size = capacity = src.size;

	return *this;
}
*/
const char* Table::getName() const
{
	return name;
}

void Table::serialize(const char* fileName)
{
	std::ofstream ofs("fileName", std::ios::binary);
	if (!ofs.is_open())
		std::cout << fileName << "could not be oppened!\n";
	else
	{
		int strLen = strlen(name);
		ofs.write((char*)&size, sizeof(int));
		ofs.write((char*)&strLen, sizeof(int));
		ofs.write((char*)&name, sizeof(char)*(strLen));

		for (int i = 0; i < size; ++i)
		{
			column[i]->serialize(ofs);
		}
	}
}

void Table::deSerialize(const char* fileName)
{
	std::ifstream ifs("fileName", std::ios::binary);
	if (!ifs.is_open())
		std::cout << fileName << "could not be oppened!\n";
	else
	{
		int strLen = 0;
		ifs.read((char*)&size, sizeof(int));
		ifs.read((char*)&strLen, sizeof(int));
		
		name = new(std::nothrow) char[strLen + 1];
		
		ifs.read((char*)&name, sizeof(char)*strLen);
		name[strLen] = '\0';

		column = new(std::nothrow) Column*[size];
		if (!column)
		{
			std::cout << "No memory for Loading the file!\n";
			return;
		}

		ColumnType tempEnum;
		for (int i = 0; i < size; ++i)
		{
			ifs.read((char*)&tempEnum, sizeof(ColumnType));
			column[i] = createColumn(tempEnum);
			column[i]->deSerialize(ifs);
		}
	}
}

void Table::addColumn(Column* newCol)
{
	if (size == capacity)
	{
		resize();
	}

	column[size] = newCol;
	++size;
}

void Table::print()
{
	const int colMerge = 10;

	int * columnWidths = new int[size];
	for (int i = 0; i < size; ++i)
	{
		int maxColWidth = 0;

		const int numberRows = column[i]->getNumberRows();
		for (int j = 0; j < numberRows; ++j)
		{
			const char *value = column[i]->getElement(j);
			maxColWidth = std::max(maxColWidth, (int)strlen(value));
		}

		columnWidths[i] = maxColWidth;
	}

	int numRows = 0;
	for (int i = 0; i < size; ++i)
		numRows = std::max(numRows, column[i]->getNumberRows());
	
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			const char* value = column[j]->getElement(i);
			int valueLen = strlen(value);

			std::cout << "| ";

			for (int i = 0; i < (columnWidths[j] - valueLen) / 2; ++i)
				std::cout << ' ';

			std::cout << value;

			for (int i = 0; i < (columnWidths[j] - valueLen) / 2 + (columnWidths[j] - valueLen) % 2; ++i)
				std::cout << ' ';

			std::cout << " |";
		}

		std::cout << '\n';
	}

	delete[] columnWidths;
}

int Table::search(int location, const char* value)
{
	int rowLocation = column[location]->findNext(value);
	return rowLocation;
}

void Table::deleteRow(int location)
{
	for (int i = 0; i < size; ++i)
	{
		column[i]->deleteElement(location);
	}
}

void Table::deleteRows(int column, const char* value)
{
	int location = search(column, value);
	while (location >= 0);
	{
		deleteRow(location);
		location = search(column, value);
	} 
}

void Table::rename(const char* str)
{
	delete[] name;
	name = new char[strlen(str) + 1];
	strcpy(name, str);
}

int Table::count(int location, const char* targetValue)
{
	int temp = 0;
	int count = -1;
	
	do
	{
		++count;
		temp = column[location]->findNext(targetValue);
	} while (temp >= 0);

	return count;
}

void Table::describe()
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << '\n' << i << ". ";
		column[i]->printType();
	}
}

void Table::update(int searchedColumn, const char* searchedValue, int targetColumn, const char* targetValue)
{
	int locationRow = 0;

	locationRow = column[searchedColumn]->findNext(searchedValue);
	while(locationRow >= 0)
	{
		column[targetColumn]->changeElement(locationRow, targetValue);	
		locationRow = column[searchedColumn]->findNext(searchedValue);
	}
}

void Table::resize()
{
	Column** arr = new(std::nothrow) Column*[size + RESIZE];
	
	for (int i = 0; i < size; ++i)
		arr[i] = column[i];

	delete[] column;
	column = arr;
}
