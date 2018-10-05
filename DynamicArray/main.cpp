#include <iostream>
#include "DynamicArray.h"

const int N = 100;
int main()
{
	DynamicArray<int> darr;
	for (int i = 0; i < N; ++i)
	{
		darr.pushBack(i);
	}

	for (int i = 0; i < N; ++i)
	{
		std::cout<<darr[i]<< ' ';
	}
	return 0;
}