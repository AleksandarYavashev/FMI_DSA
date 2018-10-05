#ifndef _BINARY_SEARCH_TREE_HEADER
#define _BINARY_SEARCH_TREE_HEADER

#include <stdexcept>

typedef int dataType;
typedef int keyType;

class BST
{
private:
	struct node
	{
		dataType data;
		keyType key;

		node* pLeft;
		node* pRight;

		node(dataType d = 0, keyType k = 0) : data(d), key(k), pLeft(nullptr), pRight(nullptr)
		{
			//...
		}

		node(const node&) = delete;
		node& operator= (const node&) = delete;
	};

	node* root;


public:
	BST();
	~BST();
	BST(const BST& other);
	BST& operator=(const BST& other);

private:
	//helper functions

	void recCopy(node*& curNode, node* otherNode);
	void recDestroy(node* curNode);

	void recInsert(node* curNode, const dataType& data, const keyType& key);
	void recRemove(node*& curNode, const keyType& key);

	dataType recSearch(node* curNode, const keyType& key)const;

};

#endif // _BINARY_SEARCH_TREE_HEADER_INCLUDED