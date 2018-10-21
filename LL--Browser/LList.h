#ifndef _LLIST_HEADER_INCLUDED_
#define _LLIST_HEADER_INCLUDED_
#include "Tab.h"

template <class T>
class LList
{
private:

	struct Node
	{
		T data;
		Node* pNext;
		Node* pPrevious;

		Node(const T& _data, Node* _pNext = nullptr, Node* _pPrevious = nullptr)
		{
			data = _data;
		}
	};


	Node* pFront;
	Node* pEnd;
	int size;

public:
	class Iterator
	{
	public:
		Iterator() { pIter = p->pFront; }
		Iterator(Node* p) {
			pIter = p;
		}

		Iterator(const Iterator& src) : pIter(src.pIter) {

		}

	public:

		Iterator& operator++()
		{
			if (pIter == p->pEnd) {
			}
			else
			{
				pIter = pIter->pNext;
			}

			return *this;
		}

		Iterator& operator++(int)
		{
			if (pIter == p->pEnd) 
			{
				return *this;
			}
			else
			{
				Iterator rtn(pIter);
				++(*this);
				return rtn;
			}
			
		}

		bool operator==(const Iterator& rhs) const
		{
			return pIter == rhs.pIter;
		}

		bool operator!=(const Iterator& rhs) const
		{
			return !(pIter == rhs.pIter);	
		}

		T& operator*()
		{
			return pIter->data;
		}

		const T& operator*() const
		{
			return pIter->data;
		}

		T* operator->()
		{
			return &(pIter->data);
		}

		const T* operator->() const
		{
			return &(pIter->data);
		}

		Iterator operator--()
		{
			if (pIter == p->pFront) {
			}
			else
			{
				pIter = pIter->pPrevious;
			}
			return *this;
		}

		Iterator operator--(int)
		{
			if (pIter == p->pFront)
			{
				return *this;
			}
			else
			{
				Iterator rtn(pIter);
				++(*this);
				return *rtn;
			}
		}

		void erease()
		{
			if (p->isEmpty())
				return;
			Node* destroy = pIter;

			if (p->getSize() == 1)
			{
				p->popFront();
				Tab* tab = new Tab("about:blank");
				p->pushFront(*tab);
				pIter = p->pFront;
			}
			else if (pIter->pPrevious == nullptr)
			{
				++pIter;
				p->popFront();
			}
			else if (pIter->pNext == nullptr)
			{
				--pIter;
				p->popEnd();
			}
			else
			{
				pIter->pNext->pPrevious = pIter->pPrevious;
				pIter->pPrevious->pNext = pIter->pNext;
				pIter = pIter->pNext;
			}

			delete[]destroy;
		}

		void insert(const Tab& tab)
		{
			Node* node = new Node(tab);
			pIter->pNext->pPrevious = node;
			pIter->pNext = node;
			pIter = node;
		}

	private:
		Node* pIter;
		LList<T>* p;
	};

	LList();
	~LList();
	LList(const LList& src);
	LList& operator=(const LList& src);

private:
	void clear();
	void copyFrom(const LList& src);
	const bool isEmpty() const { return (size==0); }
	const int getSize() const { return size; }

public:
	void pushFront(const T& value);
	void pushEnd(const T& value);

	void popFront();
	void popEnd();

	const T& Front() const;
	const T& End() const;

	Iterator getIterFront()
	{
		return Iterator(pFront);
	}

	Iterator getIterEnd()
	{
		return Iterator(pEnd);
	}
};

template<class T>
inline LList<T>::LList(): pFront(nullptr), pEnd(nullptr), size(0) {
}

template<class T>
inline LList<T>::~LList()
{
	clear();
	pFront = pEnd = nullptr;
}

template<class T>
inline LList<T>::LList(const LList & src)
{
	pFront = pEnd = nullptr;
	size = 0;
	copyFrom(src);
}

template<class T>
inline LList<T> & LList<T>::operator=(const LList & src)
{
	if (this = !&src)
	{
		clear();
		copyFrom(src);
	}

	return *this;
}

template<class T>
inline void LList<T>::clear()
{
	Node* destroy = pFront;
	Node* current = pFront;

	while (current)
	{
		destroy = current;
		current = current->pNext;
		delete destroy;
	}

	pFront = pEnd = nullptr;
	size = 0;
}

template<class T>
inline void LList<T>::copyFrom(const LList & src)
{
	if (src.isEmpty())
		return;

	try
	{
		pFront = new Node(src.pFront->data);

		Node* toCopy = src.pFront->pNext;
		Node* current = pFront;

		while (toCopy != nullptr)
		{
			current->pNext = new node(toCopy->data);
			current->pNext->pPrevious = current;
			current = current->pNext;
			toCopy = toCopy->pNext;
		}

		pEnd = current;
		pEnd->pNext = nullptr;

	}
	catch (std::bad_alloc&)
	{
		clear();
		throw;
	}

	size = src.size;
}

template<class T>
inline void LList<T>::pushFront(const T & value)
{
	if (isEmpty())
	{
		pFront = new Node(value);
		pEnd = pFront;
		pFront->pNext = pFront->pPrevious = nullptr;
		++size;
	}
	else
	{
		Node* elem = new Node(value);
		elem->pNext = pFront;
		pFront->pNext = nullptr;
		pFront->pPrevious = elem;
		pFront = elem;
		++size;
	}
}

template<class T>
inline void LList<T>::pushEnd(const T & value)
{
	if (isEmpty())
	{
		pEnd = new Node(value);
		pFront = pEnd;
		pFront->pNext = pFront->pPrevious = nullptr;
		++size;
	}
	else
	{
		pEnd->pNext = new Node(value);
		pEnd->pNext->pPrevious = pEnd;
		pEnd = pEnd->pNext;
		pEnd->pNext = nullptr;
		++size;
	}
}

template<class T>
inline void LList<T>::popFront()
{
	if (isEmpty())
	{
		std::cout << "the list is empty!\n";
		return;
	}

	if (getSize() == 1)
	{
		delete pFront;
		return;
	}

	Node* destroy = pFront;
	pFront = pFront->pNext;
	pFront->pPrevious = nullptr;
	delete destroy;
	--size;
}

template<class T>
inline void LList<T>::popEnd()
{
	if (isEmpty())
	{
		std::cout << "the list is empty!\n";
		return;
	}

	if (getSize() == 1)
	{
		delete pEnd;
		return;
	}

	Node* destroy = pEnd;
	pEnd = pEnd->pPrevious;
	pEnd->pNext = nullptr;
	delete destroy;
	--size;
}

template<class T>
inline const T & LList<T>::Front() const
{
	if (isEmpty())
	{
		throw std::exception("the list is empty");
	}

	return pFront->data;
}

template<class T>
inline const T & LList<T>::End() const
{
	if (isEmpty())
	{
		throw std::exception("the list is empty")
	}

	return pEnd->data;
}

#endif // !_LLIST_HEADER_INCLUDED_