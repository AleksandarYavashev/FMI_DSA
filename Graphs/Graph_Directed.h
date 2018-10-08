#pragma once
#include "Graph_Base.h"


class Graph_Directed : public Graph
{
public:
	Graph_Directed(std::string id) : Graph(id) {}

	virtual void createVertex(const std::string& startNode, const std::string& endNode, unsigned int weight = 1);
	virtual void deleteVertex(const std::string& startNode, const std::string& endNode);
};