#include <iostream>
#include "Merge_Sort.h"
#include <time.h>

void printArr(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr[i] << ' ';
	}

	std::cout << '\n';
}

const int size = 20;

int main()
{
	srand(time(NULL));
	int arr[size];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100;
	}

	printArr(arr, size);

	mergeSort(arr, 0, size - 1);

	printArr(arr, size);

	system("pause");
	return 0;
}