#include "BST.h"

BST::BST()
{
	root = nullptr;
}

BST::~BST()
{
	if(root != nullptr)
		recDestroy(root);
}

BST::BST(const BST & other)
{
	recCopy(root, other.root);
}

BST & BST::operator=(const BST & other)
{
	if (this != &other)
	{
		recDestroy(root);
		root = nullptr;

		recCopy(root, other.root);
	}

	return *this;
}


void BST::recCopy(node *& curNode, node * otherNode)
{	
	if (otherNode != nullptr)
	{
		curNode = new node(otherNode->data, otherNode->key);
		
		recCopy(curNode->pLeft, otherNode->pLeft);
		recCopy(curNode->pRight, otherNode->pRight);
	}

}

void BST::recDestroy(node * curNode)
{
	if (curNode != nullptr)
	{
		recDestroy(curNode->pLeft);
		recDestroy(curNode->pRight);

		delete curNode;
	}
}

void BST::recInsert(node * curNode, const dataType & data, const keyType & key)
{
	if (curNode == nullptr)
	{
		curNode = new node(data, key);
		return;
	}

	if (curNode->key == key)
		throw std::logic_error("insertion fail! Dupication of keys!");

	if (curNode->key < key)
		recInsert(curNode->pRight, data, key);
	else
		recInsert(curNode->pLeft, data, key);
}

void BST::recRemove(node *& curNode, const keyType & key)
{
	if (curNode == nullptr)
		throw std::logic_error("No such key in tree!");

	if (curNode->key < key)
	{
		recRemove(curNode->pRight, key);
		return;
	}

	if (curNode->key > key)
	{
		recRemove(curNode->pLeft, key);
		return;
	}

	if (curNode->key == key)
	{
		if (curNode->pLeft != nullptr && curNode->pRight != nullptr)
		{
			node* destr = curNode;

			node* temp = curNode->pLeft;

			while (temp->pRight != nullptr)
				temp = temp->pRight;

			curNode->data = temp->data;
			curNode->key = temp->key;

			recRemove(curNode->pLeft, curNode->key);
			return;
		}

		if (curNode->pLeft == nullptr && curNode->pRight == nullptr)
		{
			delete curNode;
			curNode = nullptr;
			return;
		}
		else
		{
			node* destr = curNode;
			
			if (curNode->pLeft)
				curNode = curNode->pLeft;
			else
				curNode = curNode->pRight;

			delete destr;
		}
	}
}

dataType BST::recSearch(node * curNode, const keyType & key) const
{
	if (curNode == nullptr)
		throw std::logic_error("No such key in tree!");

	if (curNode->key == key)
		return curNode->data;

	if (curNode->key < key)
		return recSearch(curNode->pRight, key);
	else
		return recSearch(curNode->pLeft, key);
}
