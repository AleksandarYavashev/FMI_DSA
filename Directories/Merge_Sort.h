#pragma once
#include <iostream>


void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void merge(int* arr, int low, int mid, int high, int* helpArr);

void mergeSort(int* arr, int low, int high)
{
	if ((high - low) == 1)
	{
		if (arr[low] > arr[high])
			swap(arr+low, arr+high);
		return;
	}
	else if (high == low)
		return;
	
	int mid = low + (high - low) / 2;

	int* helpArr = new int[(high - low) + 1];
	if (!(helpArr))
	{
		std::cout << "no memory";
		return;
	}

	mergeSort(arr, low, mid);
	mergeSort(arr, mid + 1, high);

	merge(arr, low, mid, high, helpArr);

	delete[] helpArr;
}

void merge(int* arr, int low, int mid, int high, int* helpArr)
{
	int k=0;
	int i = low;
	int j = mid + 1;
	
	while(i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
		{
			helpArr[k] = arr[i];
			++i;
		}
		else
		{
			helpArr[k] = arr[j];
			++j;
		}

		++k;
	}

	//if there are any elems left in the first - copy them
	while (i <= mid)
	{
		helpArr[k] = arr[i];
		++i;
		++k;
	}

	//if there are any elems left in the second - copy them
	while (j <= high)
	{
		helpArr[k] = arr[j];
		++j;
		++k;
	}

	i = 0;
	j = low;
	while (j<= high)
	{
		arr[j] = helpArr[i];
		++j;
		++i;
	}
}