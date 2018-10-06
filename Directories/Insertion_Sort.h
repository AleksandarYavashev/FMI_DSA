#pragma once

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


void insertionSort(int* arr, int size)
{
	for (int i = 1; i < size; ++i)
	{
		for (int j = i-1; j >= 0; --j)
		{
			if (arr[i] < arr[j])
				swap(&arr[i], &arr[j]);
			else
				break;
		}
	}
}