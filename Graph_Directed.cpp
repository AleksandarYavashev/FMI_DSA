#include "Graph_Directed.h"

void Graph_Directed::createVertex(const std::string& startNode, const std::string& endNode, unsigned int weight)
{

	unsigned int startID = hash(startNode);
	unsigned int endID = hash(endNode);

	auto searchStart = nodes.find(startID);
	auto searchEnd = nodes.find(endID);

	// Nodes exist.
	if (searchStart != nodes.end() && searchEnd != nodes.end())
	{
		nodes[startID]->vertices.insert({ endID, weight });
	}
	// Node/s does not exist.
	else
	{
		std::cout << "Node/s does not exist. Vertex not created.\n";
	}

}

void Graph_Directed::deleteVertex(const std::string& startNode, const std::string& endNode)
{
	unsigned int startID = hash(startNode);
	unsigned int endID = hash(endNode);

	nodes[startID]->vertices.erase(endID);
}