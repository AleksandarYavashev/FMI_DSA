#include "Graph_Undirected.h"
#include <list>
#include <stack>
#include <unordered_set>

void Graph_Undirected::createVertex(const std::string& startNode, const std::string& endNode, unsigned int weight)
{
	unsigned int startID = hash(startNode);
	unsigned int endID = hash(endNode);

	auto searchStart = nodes.find(startID);
	auto searchEnd = nodes.find(endID);

	// Nodes exist.
	if (searchStart != nodes.end() && searchEnd != nodes.end())
	{
		nodes[startID]->vertices.insert({ endID, weight });

		nodes[endID]->vertices.insert({ startID, weight });
	}
	// Node/s does not exist.
	else
	{
		std::cout << "Node/s does not exist. Vertex not created.\n";
	}

}

void Graph_Undirected::deleteVertex(const std::string& startNode, const std::string& endNode)
{
	unsigned int startID = hash(startNode);
	unsigned int endID = hash(endNode);

	nodes[startID]->vertices.erase(endID);
	nodes[endID]->vertices.erase(startID);
}






