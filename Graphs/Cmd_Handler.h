#pragma once
#include "Graph_Handler.h"

class CmdHandler
{
public:
	void run()
	{

		while (std::cin >> arg)
			callCommand(arg);
	}

private:
	GraphHandler graphHandle;

private:

	std::string arg;

	void createVertex();
	void createNode();
	void createGraph();

	void deleteVertex();
	void deleteNode();
	void deleteGraph();

	void useGraph();

	void search();

	void callCommand(std::string command)
	{
		if (command.compare("CREATE") == 0)
		{
			std::cin >> arg;

			if (arg.compare("ARC") == 0)
				createVertex();

			if (arg.compare("NODE") == 0)
				createNode();

			if(arg.compare("GRAPH") == 0)
				createGraph();

		}

		else if (command.compare("DELETE") == 0)
		{
			std::cin >> arg;

			if (arg.compare("ARC") == 0)
				deleteVertex();
			
			if (arg.compare("NODE") == 0)
				deleteNode();

			if (arg.compare("GRAPH") == 0)
				deleteGraph();

		}

		else if (command.compare("USE") == 0)
		{	
			std::cin >> arg;
			if (arg.compare("GRAPH") == 0)
				useGraph();
		}

		else if (command.compare("SEARCH") == 0)
		{
			search();
		}
		
		else
		{
			std::cout << "Wrong command input.\n";
		}
	}
};


inline void CmdHandler::createVertex()
{
	std::string startNode;
	std::string  endNode;
	std::string strWeight;
	std::cin >> startNode >> endNode;
	std::getline(std::cin, strWeight);

	if (!strWeight.empty())
	{
		unsigned int weight = std::stoi(strWeight, nullptr, 10);
		graphHandle.createVertex(startNode, endNode, weight);
	}
	else
	{
		graphHandle.createVertex(startNode, endNode);
	}
	
}

inline void CmdHandler::createNode()
{
	std::string nodeID;
	std::cin >> nodeID;

	graphHandle.createNode(nodeID);
}

inline void CmdHandler::createGraph()
{
	std::string graphID;
	std::string directed;
	std::cin >> graphID;

	std::getline(std::cin, directed);

	if (directed.empty())
		graphHandle.createGraph(graphID);
	else
		graphHandle.createDirectedGraph(graphID);
}

inline void CmdHandler::deleteVertex()
{
	std::string startNode;
	std::string endNode;

	std::cin >> startNode >> endNode;

	graphHandle.deleteVertex(startNode, endNode);
}

inline void CmdHandler::deleteNode()
{
	std::string nodeID;
	std::cin >> nodeID;

	graphHandle.deleteNode(nodeID);
}

inline void CmdHandler::deleteGraph()
{
	std::string graphID;
	std::cin >> graphID;

	graphHandle.deleteGraph(graphID);
}

inline void CmdHandler::search()
{
	std::string startNode;
	std::string endNode;
	std::string algorithm;

	std::cin >> startNode >> endNode >> algorithm;

	graphHandle.search(startNode, endNode, algorithm);
}

inline void CmdHandler::useGraph()
{
	std::string graphID;
	std::cin >> graphID;

	graphHandle.useGraph(graphID);
}