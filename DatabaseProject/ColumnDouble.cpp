#include "ColumnDouble.h"

double ColumnDouble::convertToDouble(const char* str)
{
	double x = atof(str);
	return x;
}

ColumnDouble::ColumnDouble(int _size, double* _arr)
{
	arr = _arr;
	size = capacity = _size;
	type = ColumnType::DOUBLE;
}

void ColumnDouble::resize()
{
	double* temp = new(std::nothrow) double[size * 2 + 1];
	if (!temp)
	{
		std::cout << "No space for resizing// ColumnDouble\n";
	}

	for (int i = 0; i < size; ++i)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;

	capacity = size * 2 + 1;
}

void ColumnDouble::addElement(const char* str)
{
	double num = convertToDouble(str);

	if (capacity == size)
	{
		resize();
	}

	arr[size] = num;
	++size;
}

void ColumnDouble::serialize(std::ofstream& ofs) const
{
	ofs.write((char*)&type, sizeof(ColumnType));
	ofs.write((char*)&size, sizeof(int));
	ofs.write((char*)&arr, sizeof(double)*size);
}

void ColumnDouble::deSerialize(std::ifstream& ifs)
{
	int tempSize = 0;

	ifs.read((char*)&tempSize, sizeof(int));
	arr = new(std::nothrow) double[tempSize];
	if (!arr)
	{
		std::cout << "No memory for Loading the file!\n";
		return;
	}

	size = capacity = tempSize;

	ifs.read((char*)&arr, sizeof(double)*size);
}

void ColumnDouble::deleteElement(int location)
{
	double* tempArr = new(std::nothrow) double[--size];
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

void ColumnDouble::changeElement(int location, const char* str)
{
	double value = convertToDouble(str);
	arr[location] = value;
}

const char* ColumnDouble::getElement(int rowIndex) const
{
	if (rowIndex >= size) return "NULL";

	static char value[VALUE_LENGTH_MAX];
	snprintf(value, sizeof(value), "%lf", arr[rowIndex]);
	return value;
}

int ColumnDouble::findNext(const char* str)
{
	double value = convertToDouble(str);

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

void ColumnDouble::printType() const
{
	std::cout << "DOUBLE";
}

void ColumnDouble::startFind()
{
	currLocation = 0;
}