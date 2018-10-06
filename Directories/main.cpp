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
	// Ако потребителят не е указал коя папка да се сканира,
	// извежда се съобщение за това как да се използва програмата.
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <path>\n\n";
		system("pause");
		return 1;
	}

	std::cout << "Scanning " << argv[1] << "...\n";

	// Поради улесняващите условия в задачата, считаме, че
	// всички файлове ще бъдат с път не по-дълъг от 260 символа,
	// колкото е стойността на MAX_PATH за Windows. 
	char path[MAX_PATH + 3];


	// При подаден път от вида C:\Temp\SomeDirectory,
	// конструира маска от вида C:\Temp\SomeDirectory\*
	// Ако потребителят подаде пътя накрая с наклонена черта,
	// например ето така: C:\Temp\SomeDirectory,
	// ще се конструира маска от вида C:\Temp\SomeDirectory\\*,
	// но това е ОК, защото системата ще го коригира.
	strcpy_s(path, MAX_PATH, argv[1]);
	strcat_s(path, MAX_PATH, "\\*");


	// файл в който записваме всички файлове удовлетворяващи търенето
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

	// намираме броя на файлове на които трябва да разделим оригиналният
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

	// буфер за копиране
	char* buffer = new char[newSize * sizeof(fileData)];

	// създаване на помощните файлове
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
	
	// ако има незаписани байтове ги допълваме в последния файл
	unsigned long long curPos = iFileInfo.tellg();
	
	if (size - curPos)
	{
		iFileInfo.read(buffer, size - curPos);
		streamArr[counter - 1].write(buffer, size - curPos);
	}


	// сортираме новосъздадените файлове

	fileData* fileArr = new fileData[size / sizeof(fileData)];
	for (int i = 0; i < counter - 1; ++i)
	{
		// зареждаме файла в паметта
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


	// Почистваме
	for (int i = 0; i < counter; ++i)
	{
		streamArr[i].close();
	}

	iFileInfo.close();

	// външно сортиране
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
	// тук ще записваме информацията за файла
	fileData fData;


	// Намираме първия файл в директорията
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(path, &ffd);

	// Ако операцията е била неуспешна, извеждаме съобщение за грешка
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "FindFirstFile failed! Error code is " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}


	//Създаваме контейнер за намерените директории
	std::vector<WIN32_FIND_DATA> dirArr;


	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Намереният елемент е директория и я добавяме в масива.
			dirArr.push_back(ffd);
		}
		else
		{
			// проверка на името +
			// запис във файла
			if (extensionMatch(path, ffd.cFileName)) 
			{
				strcpy(fData.name, ffd.cFileName);
				fData.size = ffd.nFileSizeLow;
				ofs.write(reinterpret_cast<char*>(&fData), sizeof(fileData));
			}
		}

	} while (FindNextFile(hFind, &ffd) != 0);


	// От горния цикъл можем да излезем или ако възникне грешка,
	// или ако обходим всички елементи в директорията.
	// По-долу проверяваме дали второто е вярно.
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		std::cout << "FindNextFile failed! Error code is " << GetLastError() << std::endl;
		return 1;
	}

	// викаме обхождащата функция за всички намерени директории.
	int stopper = dirArr.size();
	for (int i = 0; i < stopper; ++i)
	{
		ffd = dirArr.back();
		dirArr.pop_back();
		searchDir(ffd.cFileName, ofs);
	}

	// Накрая трябва да се почисти.
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
