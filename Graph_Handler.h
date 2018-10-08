#pragma once
#include "Graph_Directed.h"
#include "Graph_Undirected.h"

class GraphHandler
{
private:
	std::unordered_map<std::string, Graph*> graphs;
	Graph* current;
		
public:
	GraphHandler() {
		current = nullptr;
	}
	~GraphHandler();

	GraphHandler(const GraphHandler&) = delete;
	GraphHandler& operator=(const GraphHandler&) = delete;

	void createVertex(const std::string& startNode, const std::string& endNode, unsigned int weight = 1);

	void createNode(const std::string& nodeID);

	void createGraph(const std::string& graphID);

	void createDirectedGraph(const std::string& graphID);

	void deleteVertex(const std::string& startNode, const std::string& endNode);

	void deleteNode(const std::string& nodeID);

	void deleteGraph(const std::string& graphID);

	void search(const std::string& startNode, const std::string& endNode, const std::string& algorithm);

	void useGraph(const std::string& graphID);
};