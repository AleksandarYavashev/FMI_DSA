#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>


static unsigned int hash(const std::string& str)
{
	unsigned int h = 1;

	for (auto it : str)
		h = ((unsigned long long)h * 29 + it) % 1000000009;
	
	return h;
}


template <class T>
struct Stack
{
	std::stack<T> stack;
	T front() { return stack.top(); }
	void push(T& value) { stack.push(value); }
	void pop() { stack.pop(); }
	bool empty() { return stack.empty(); }
};


struct Node
{
	std::string strID;
	std::unordered_map<unsigned int, unsigned int> vertices;   //ID , weight

	Node(std::string _id) : strID(_id) {}
};


class Graph
{
protected:
	std::string strID;
	std::unordered_map<unsigned int, Node*> nodes;

	template <class Container>
	void algorithm(const std::string& startNode, const std::string& endNode);

public:
	Graph(std::string name);
	virtual ~Graph();
	Graph(const Graph& src) = delete;
	Graph& operator=(const Graph& src) = delete;

	//interface
	
	void createNode(std::string  _id);
	void deleteNode(std::string _id);

	virtual void createVertex(const std::string& startNode, const std::string& endNode, unsigned int weight = 1) = 0;
	virtual void deleteVertex(const std::string& startNode, const std::string& endNode) = 0;

	void BFS(const std::string& startNode, const std::string& endNode);

	void dfsShortest(const std::string& startNode, const std::string& endNode);
	void dfsLongest(const std::string startNode, const std::string& endNode)const {}

	void dijkstra(const std::string& startNode, const std::string& endNode)const {}

};


