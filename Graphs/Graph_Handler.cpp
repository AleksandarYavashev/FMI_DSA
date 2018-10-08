#include "Graph_Handler.h"

GraphHandler::~GraphHandler()
{
	Graph* destroyer;
	for (auto it = graphs.begin(); it != graphs.end(); ++it)
	{
		destroyer = it->second;
		delete destroyer;
	}
}

void GraphHandler::createVertex(const std::string & startNode, const std::string & endNode, unsigned int weight)
{
	if (current == nullptr)
	{
		std::cout << "Chose a graph with the <USE> command.\n";
		return;
	}

	current->createVertex(startNode, endNode, weight);
}

void GraphHandler::createNode(const std::string & nodeID)
{
	if (current == nullptr)
	{
		std::cout << "Chose a graph with the <USE> command.\n";
		return;
	}

	current->createNode(nodeID);
}

void GraphHandler::createGraph(const std::string & graphID)
{
	Graph* newGraph = new Graph_Undirected(graphID);

	// Added graph succesfully and made it current
	if (graphs.insert({ graphID, newGraph }).second)
	{
		current = newGraph;
	}

	// existing graph with same ID
	else
	{
		std::cout << "Graph with ID: \"" << graphID << "\" already existing.\n";
	}

}

void GraphHandler::createDirectedGraph(const std::string & graphID)
{
	Graph* newGraph = new Graph_Directed(graphID);

	// Added graph succesfully and made it current
	if (graphs.insert({ graphID, newGraph }).second)
	{
		current = newGraph;
	}

	// existing graph with same ID
	else
	{
		std::cout << "Graph with ID: \"" << graphID << "\" already existing.\n";
	}

}

void GraphHandler::deleteVertex(const std::string & startNode, const std::string & endNode)
{
	if (current == nullptr)
	{
		std::cout << "Chose a graph with the <USE> command.\n";
		return;
	}

	current->deleteVertex(startNode, endNode);
}

void GraphHandler::deleteNode(const std::string & nodeID)
{
	if (current == nullptr)
	{
		std::cout << "Chose a graph with the <USE> command.\n";
		return;
	}

	current->deleteNode(nodeID);
}

void GraphHandler::deleteGraph(const std::string & graphID)
{
	auto search = graphs.find(graphID);

	
	if (search != graphs.end())
	{
		if (search->second == current)
		{
			current = nullptr;
		}

		graphs.erase(graphID);
	}
	else
		std::cout << "Graph with ID: \"" << graphID << "\" does not exist.\n";
}

void GraphHandler::search(const std::string & startNode, const std::string & endNode, const std::string & algorithm)
{
	if (algorithm.compare("bfs") == 0)
		current->BFS(startNode, endNode);
	else if (algorithm.compare("dfs-shortest") == 0)
		current->dfsShortest(startNode, endNode);
	else if (algorithm.compare("dfs-longest") == 0)
		current->dfsLongest(startNode, endNode);
	else if (algorithm.compare("dijkstra") == 0)
		current->dijkstra(startNode, endNode);
	else
		std::cout << "Wrong algorithm input.\n";
}

void GraphHandler::useGraph(const std::string & graphID)
{
	auto search = graphs.find(graphID);
	if (search != graphs.end())
		current = graphs[graphID];
	else
		std::cout << "Graph with ID: \"" << graphID << "\" does not exist.\n";
}
