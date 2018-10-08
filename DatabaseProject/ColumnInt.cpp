#include "ColumnInt.h"

int ColumnInt::convertToInt(const char* str)
{
	int x = atoi(str);
	return x;
}

ColumnInt::ColumnInt(int _size, int* _arr)
{
	arr = _arr;
	size = capacity = _size;
	type = ColumnType::INT;
}

void ColumnInt::resize()
{
	int* temp = new(std::nothrow) int[capacity + RESIZE];
	if (!temp)
	{
		std::cout << "No space for resizing// ColumnInt\n";
	}

	for (int i = 0; i < size; ++i)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;

	capacity += RESIZE;
}

void ColumnInt::addElement(const char* str)
{
	int num = convertToInt(str);

	if (capacity == size)
	{
		resize();
	}

	arr[size] = num;
	++size;
}

const char * ColumnInt::getElement(int rowIndex) const
{
	if (rowIndex >= size) return "NULL";

	static char value[VALUE_LENGTH_MAX];
	snprintf(value, sizeof(value), "%d", arr[rowIndex]);
	return value;
}

void ColumnInt::serialize(std::ofstream& ofs) const
{
	ofs.write((char*)&type, sizeof(ColumnType));
	ofs.write((char*)&size, sizeof(int));
	ofs.write((char*)&arr, sizeof(int)*size);
}

void ColumnInt::deSerialize(std::ifstream& ifs)
{
	int tempNum = 0;

	ifs.read((char*)&tempNum, sizeof(int));
	arr = new(std::nothrow) int[size];
	if (!arr)
	{
		std::cout << "No memory for Loading the file!\n";
		return;
	}

	size = capacity = tempNum;

	ifs.read((char*)&arr, sizeof(int)*size);
}

void ColumnInt::deleteElement(int location)
{
	int* tempArr = new(std::nothrow) int[--size];
	if (!tempArr)
	{
		std::cout << "No memory for tempArr// deleting\n";
	}

	for (int i = 0; i < location; ++i)
	{
		tempArr[i] = arr[i];
	}

	for (int i = location; i < size; ++i)
	{
		tempArr[i] = arr[i + 1];
	}

	delete[] arr;
	arr = tempArr;
	startFind();
}

void ColumnInt::changeElement(int location, const char* str)
{
	int value = convertToInt(str);
	arr[location] = value;
}

int ColumnInt::findNext(const char* str)
{
	int value = convertToInt(str);

	for (int i = currLocation; i <= size; ++i)
	{
		if (i == size)
		{
			return INVALID_INDEX;
		}

		if (arr[i] == value)
		{
			currLocation = i;
			return i;
		}

		return INVALID_INDEX;
	}
}

void ColumnInt::printType() const
{
	std::cout << "INT";
}

void ColumnInt::startFind()
{
	currLocation = 0;
}