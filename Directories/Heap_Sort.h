#pragma once
#include "External_Sort.h"

void swap(fileData* x, fileData* y)
{
	fileData temp = *x;
	*x = *y;
	*y = temp;
}


void heapify(fileData* arr, int size, int pos)
{
	int max = pos;
	int left = pos * 2;
	int right = left + 1;

	if (left < size && arr[left] < arr[max])
		max = left;

	if (right < size && arr[right] < arr[left])
		max = right;

	if (max != pos)
	{
		swap(&arr[pos], &arr[max]);
		heapify(arr, size, max);
	}
}

void buildHeap(fileData* arr, int size)
{
	for (int i = size / 2; i >= 0; --i)
	{
		heapify(arr, size, i);
	}
}

void heapSort(fileData* arr, int size)
{
	buildHeap(arr, size);

	for (int i = size - 1; i >= 0; --i)
	{
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}




