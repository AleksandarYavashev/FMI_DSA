#include "ColumnString.h"

void ColumnString::resize()
{
	char** temp = new(std::nothrow) char*[size * 2 + 1];
	if (!temp)
	{
		std::cout << "No space for resizing// ColumnSTRING\n";
	}

	for (int i = 0; i < size; ++i)
	{
		temp[i] = str[i];
	}

	delete[] str;
	str = temp;

	capacity = size * 2 + 1;
}

ColumnString::~ColumnString()
{
	for (int i = 0; i < size; ++i)
	{
		delete[] str[i];
	}

	delete[] str;
}

void ColumnString::serialize(std::ofstream& ofs) const
{
	ofs.write((char*)&type, sizeof(ColumnType));
	ofs.write((char*)&size, sizeof(int));

	int length = 0;
	for (int i = 0; i < size; ++i)
	{
		length = strlen(str[i]);
		ofs.write((char*)&length, sizeof(int));
		ofs.write((char*)&str[i], sizeof(char)*length);
	}
	
}

void ColumnString::deSerialize(std::ifstream& ifs)
{
	int tempSize = 0;

	ifs.read((char*)&tempSize, sizeof(int));
	str = new(std::nothrow) char*[tempSize];
	if (!str)
	{
		std::cout << "No memory for Loading the file!\n";
		return;
	}

	size = capacity = tempSize;
	
	for (int i = 0; i < size; ++i)
	{
		ifs.read((char*)&tempSize, sizeof(int));
		str[i] = new char[tempSize + 1];
		ifs.read((char*)&str[i], (sizeof(char)*tempSize));
		str[tempSize] = '\0';
	}
}

void ColumnString::addElement(const char* value)
{
	if (size == capacity)
	{
		resize();
	}

	char* temp = new char[strlen(value) + 1];
	strcpy(temp, value);
	str[size] = temp;
	++size;
}

const char * ColumnString::getElement(int rowIndex) const
{
	if (rowIndex >= size) return "NULL";

	return str[rowIndex];
}

void ColumnString::deleteElement(int location)
{
	delete[] str[location];
	++location;
	for (int i = location; i < size; ++i)
	{
		str[i] = str[i + 1];
	}

	--size;
	startFind();
}

void ColumnString::changeElement(int location, const char* value)
{
	delete[] str[location];
	str[location] = new char[strlen(value) + 1];
	strcpy(str[location], value);
}

void ColumnString::startFind()
{
	currLocation = 0;
}

int ColumnString::findNext(const char* value)
{
	for (int i = currLocation; i <= size; ++i)
	{
		if (i == size)
		{
			return INVALID_INDEX;
		}

		if (strcmp(str[i],value))
		{
			currLocation = i;
			return i;
		}

		return INVALID_INDEX;
	}
}

void ColumnString::printType() const
{
	std::cout << "STRING";
}