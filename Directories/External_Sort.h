#pragma once
#include <windows.h>
#include <fstream>
struct fileData
{
	char name[MAX_PATH + 3];
	unsigned long size;
	bool operator< (const fileData& other)
	{
		if (size < other.size)
			return true;
		else if (size == other.size && (strcmp(name, other.name) < 0))
			return true;
		else
			return false;
	}
};

struct node
{
	fileData element;
	int index;
	
	node(fileData elem, int x) :element(elem), index(x) {
		//
	}
	node() {};
};

void swap(node* x, node* y)
{
	node temp = *x;
	*x = *y;
	*y = temp;	
}


// HEAP

class MaxHeap
{
private:
	node* array;
	int size;

public:
	MaxHeap(node* arr, int size);
	
	void heapify(int index);

	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }

	node getMin() { return array[0]; }
	int getSize()const { return size; }

	void swapMin(node n);
	void deleteMin();
	
};

MaxHeap::MaxHeap(node* arr, int _size)
{
	array = arr;
	size = _size;
	for (int i = size / 2; i >= 0; --i)
		heapify(i);
}

void MaxHeap::heapify(int index)
{
	int min = index;
	int l = left(index);
	int r = right(index);
	if (l < size && array[min].element < array[l].element)
		min = l;
	if (l < size && array[min].element < array[r].element)
		min = r;
	if (min != index)
	{
		swap(&array[index], &array[min]);
		heapify(min);
	}
}

void MaxHeap::swapMin(node elem)
{
	array[0] = elem;
	heapify(0);
}

void MaxHeap::deleteMin()
{
	swap(&array[0], &array[size]);
	--size;
	heapify(0);
}


// -----------------------------------------------------------------
//Merge


void mergeFiles(int count)
{
	char str[4];
	std::ifstream* streamArr = new std::ifstream[count];
	for (int i = 0; i < count; ++i)
	{
		_itoa(i, str, 10);
		streamArr[i].open(str, std::ios::in | std::ios::binary);
	}
	fileData* array = new fileData[count];
	for (int i = 0; i < count; ++i)
	{
		streamArr[i].read(reinterpret_cast<char*>(&array[i]), sizeof(fileData));
	}

	node* nodeArr = new node[count];
	
	for (int i = 0; i < count; ++i)
	{
		nodeArr[i].element = array[i];
		nodeArr[i].index = i;
	}
	
	// not using fileData array anymore
	delete[] array;

	// building heap
	MaxHeap heap(nodeArr, count);

	// sorted file
	std::ofstream newFile("sorted", std::ios::out | std::ios::binary);

	fileData fileDat;
	node elem;
	int index; // index of elemet's file

	while (true)
	{
		if (heap.getSize())
			break;

		fileDat = heap.getMin().element;
		index = heap.getMin().index;

		newFile.write(reinterpret_cast<char*>(&fileDat), sizeof(fileData));
		
		if (streamArr[index].eof())
		{
			heap.deleteMin();
			continue;
		}

		streamArr[index].read(reinterpret_cast<char*>(&elem), sizeof(node));
		heap.swapMin(elem);
	}

	delete[] nodeArr;
	delete[] streamArr;
}