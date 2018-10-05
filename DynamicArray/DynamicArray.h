#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

const int INITIAL_SIZE = 10;

template <class T>
class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(const DynamicArray& src);
	DynamicArray& operator=(const DynamicArray& src);
	~DynamicArray();

public:
	void pushBack(T element);

	const T& operator[](int pos) const;
	T& operator[] (int pos);
	
private:
	void resize();
	void copy(DynamicArray& other);
	void clear();

private:
	T* data;
	int size;
	int capacity;
};

template<class T>
inline void DynamicArray<T>::resize()
{
	T* tempArr = new T[size * 2 + 1];

	for (int i = 0; i < size; ++i)
	{
		tempArr[i] = data[i];
	}

	delete[] data;
	data = tempArr;
	capacity = size * 2 + 1;
}

template<class T>
inline void DynamicArray<T>::copy(DynamicArray<T>& other)
{
	for (int i = 0; i < other.size; ++i)
	{
		data[i] = other.data[i];
	}
	
	size = other.size;
	capacity = other.capacity;
}

template<class T>
inline void DynamicArray<T>::clear()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template<class T>
inline DynamicArray<T>::DynamicArray()
{
	data = new T[INITIAL_SIZE];
	size = 0;
	capacity = 10;
}

template<class T>
inline DynamicArray<T>::DynamicArray(const DynamicArray & src)
{
	data = new T[src.capacity];
	copy(src);
}

template<class T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& src)
{
	if (this != &src)
	{
		clear();
		copy(src);
	}

	retrun *this;
}

template<class T>
inline DynamicArray<T>::~DynamicArray()
{
	clear();
}

template<class T>
inline void DynamicArray<T>::pushBack(T element)
{
	if (size == capacity)
		resize();
	
	data[size] = element;
	++size;
}

template<class T>
inline const T & DynamicArray<T>::operator[](int pos) const
{
	return data[pos];
}

template<class T>
inline T & DynamicArray<T>::operator[](int pos)
{
	return data[pos];
}

#endif	// _DYNAMIC_ARRAY_INCLUDED