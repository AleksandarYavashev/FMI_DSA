/* Sources:
*
* URL: https://github.com/semerdzhiev/sdp-samples Author : Atanas Semerdzhiev
* 
* --------------------------------------------------------------
* Aleksandar Yavashev 
* FN 45216
* Visual Studio 2017
*/


#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "External_Sort.h"
#include "Heap_Sort.h"

bool extensionMatch(char* extension, char* fileName);
bool searchDir(char* path, std::ofstream& ofs);
void printFile(unsigned long long size, int counter);

int main(int argc, char *argv[])
{
	// ��� ������������ �� � ������ ��� ����� �� �� �������,
	// ������� �� ��������� �� ���� ��� �� �� �������� ����������.
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <path>\n\n";
		system("pause");
		return 1;
	}

	std::cout << "Scanning " << argv[1] << "...\n";

	// ������ ������������ ������� � ��������, �������, ��
	// ������ ������� �� ����� � ��� �� ��-����� �� 260 �������,
	// ������� � ���������� �� MAX_PATH �� Windows. 
	char path[MAX_PATH + 3];


	// ��� ������� ��� �� ���� C:\Temp\SomeDirectory,
	// ���������� ����� �� ���� C:\Temp\SomeDirectory\*
	// ��� ������������ ������ ���� ������ � ��������� �����,
	// �������� ��� ����: C:\Temp\SomeDirectory,
	// �� �� ���������� ����� �� ���� C:\Temp\SomeDirectory\\*,
	// �� ���� � ��, ������ ��������� �� �� ��������.
	strcpy_s(path, MAX_PATH, argv[1]);
	strcat_s(path, MAX_PATH, "\\*");


	// ���� � ����� ��������� ������ ������� ��������������� ��������
	std::ofstream oFileInfo("fileInfo", std::ios::out | std::ios::binary);
	if (!oFileInfo.is_open())
	{
		std::cout << "Cannot open output file stream.\n";
		return 2;
	}

	
	if (searchDir(path, oFileInfo))
		return 3;

	oFileInfo.close();
	

	std::ifstream iFileInfo("fileInfo", std::ios::in | std::ios::binary);

	// getting file's size
	iFileInfo.seekg(0, std::ios::end);
	unsigned long long size = iFileInfo.tellg();
	iFileInfo.seekg(0, std::ios::beg);

	int counter = 2;
	size = size / sizeof(fileData);
	unsigned long long newSize = size / 2;

	// �������� ���� �� ������� �� ����� ������ �� �������� ������������
	while (true)
	{
		fileData* test = new (std::nothrow) fileData[newSize];

		if (test)
			break;
		else
		{
			counter += 2;
			newSize = size / counter;
		}
	}

	// ����� �� ��������
	char* buffer = new char[newSize * sizeof(fileData)];

	// ��������� �� ��������� �������
	char str[4];
	std::fstream* streamArr = new std::fstream[counter];
	for (int i = 0; i < counter; ++i)
	{
		_itoa(i, str, 10);
		streamArr[i].open(str, std::ios::out | std::ios::binary);
		if (!streamArr->is_open())
		{
			std::cout << "Error in creating files for partitioning.\n";
			system("pause");
			return 4;
		}

		iFileInfo.read(buffer, newSize * sizeof(fileData));
		streamArr[i].write(buffer, newSize * sizeof(fileData));
	}
	
	// ��� ��� ���������� ������� �� ��������� � ��������� ����
	unsigned long long curPos = iFileInfo.tellg();
	
	if (size - curPos)
	{
		iFileInfo.read(buffer, size - curPos);
		streamArr[counter - 1].write(buffer, size - curPos);
	}


	// ��������� ��������������� �������

	fileData* fileArr = new fileData[size / sizeof(fileData)];
	for (int i = 0; i < counter - 1; ++i)
	{
		// ��������� ����� � �������
		streamArr[i].seekg(0, std::ios::beg);
		streamArr[i].read(reinterpret_cast<char*>(&fileArr), newSize * sizeof(fileData));

		heapSort(fileArr, newSize);

		streamArr[i].seekp(0, std::ios::beg);
		streamArr[i].write(reinterpret_cast<char*>(&fileArr), newSize * sizeof(fileData));
	}

	streamArr[counter - 1].seekg(0, std::ios::beg);
	streamArr[counter - 1].read(reinterpret_cast<char*>(&fileArr), (newSize * sizeof(fileData) + size - curPos));
	heapSort(fileArr, (newSize + ((size - curPos) / sizeof(fileData))));
	streamArr[counter - 1].seekp(0, std::ios::beg);
	streamArr[counter - 1].write(reinterpret_cast<char*>(&fileArr), (newSize * sizeof(fileData)+size-curPos));


	// ����������
	for (int i = 0; i < counter; ++i)
	{
		streamArr[i].close();
	}

	iFileInfo.close();

	// ������ ���������
	mergeFiles(counter);
	
	printFile(newSize, counter);

	system("pause");
	
	return 0;
}



// --------------------------------------------------



bool extensionMatch(char* extension, char* fileName)
{
	int extensionLen = strlen(extension);
	int fNameLen = strlen(fileName);

	if (fileName[fNameLen - extensionLen - 1] != '.')
		return false;
	else
	{
		for (int i = 0; i < extensionLen; ++i)
		{
			if (extension[i] != fileName[fNameLen - extensionLen + i])
				return false;
		}
	}

	return true;
}

bool searchDir(char* path, std::ofstream& ofs)
{
	// ��� �� ��������� ������������ �� �����
	fileData fData;


	// �������� ������ ���� � ������������
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(path, &ffd);

	// ��� ���������� � ���� ���������, ��������� ��������� �� ������
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "FindFirstFile failed! Error code is " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}


	//��������� ��������� �� ���������� ����������
	std::vector<WIN32_FIND_DATA> dirArr;


	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// ���������� ������� � ���������� � � �������� � ������.
			dirArr.push_back(ffd);
		}
		else
		{
			// �������� �� ����� +
			// ����� ��� �����
			if (extensionMatch(path, ffd.cFileName)) 
			{
				strcpy(fData.name, ffd.cFileName);
				fData.size = ffd.nFileSizeLow;
				ofs.write(reinterpret_cast<char*>(&fData), sizeof(fileData));
			}
		}

	} while (FindNextFile(hFind, &ffd) != 0);


	// �� ������ ����� ����� �� ������� ��� ��� �������� ������,
	// ��� ��� ������� ������ �������� � ������������.
	// ��-���� ����������� ���� ������� � �����.
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		std::cout << "FindNextFile failed! Error code is " << GetLastError() << std::endl;
		return 1;
	}

	// ������ ����������� ������� �� ������ �������� ����������.
	int stopper = dirArr.size();
	for (int i = 0; i < stopper; ++i)
	{
		ffd = dirArr.back();
		dirArr.pop_back();
		searchDir(ffd.cFileName, ofs);
	}

	// ������ ������ �� �� �������.
	FindClose(hFind);

	return 0;
}

void printFile(unsigned long long size, int counter)
{
	fileData* arr = new fileData[size];

	std::ifstream ifs("sorted", std::ios::in | std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "could not open file.\n";
		return;
	}


	for (int i = 0; i < counter; ++i)
	{
		ifs.read(reinterpret_cast<char*>(&arr), size * sizeof(fileData));

		for (int j = 0; j < size; ++j)
		{
			std::cout << arr[i].name << '\n';
		}
	}

	ifs.close();
}
