#include "Graph_Base.h"


template <class Container>
void Graph::algorithm(const std::string& startNode, const std::string& endNode)
{
	unsigned int endNodeID = hash(endNode);
	unsigned int startNodeID = hash(startNode);

	std::unordered_set<unsigned int> visited;


	Container queue;

	visited = { startNodeID };
	queue.push(std::vector<unsigned int>(1, startNodeID));

	std::string curNodeSTR;

	while (!queue.empty() && queue.front().back() != endNodeID)
	{
		auto curNodeID = queue.front();
		//searchStr(curNodeID.back(), curNodeSTR);

		Node* pCurNode = nodes[curNodeID.back()];

		auto it = pCurNode->vertices.begin();

		for (; it != pCurNode->vertices.end() && !(visited.insert(it->first)).second; ++it);

		if (it == pCurNode->vertices.end())
			queue.pop();
		else
		{
			curNodeID.push_back(it->first);
			queue.push(curNodeID);
		}
	}

	if (queue.empty())
	{
		std::cout << "No path from " << startNode << " to " << endNode << "\n";
	}

	else
	{
		std::cout << "There is a path!\n";
		for (auto &it : queue.front())
		{
			std::cout << nodes[it]->strID << '\n';
		}
	}
}


Graph::Graph(std::string name)
{
	strID = name;
}


Graph::~Graph()
{
	Node* destroyer;
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		destroyer = it->second;
		delete destroyer;
	}
}


void Graph::createNode(std::string _id)
{
	unsigned int hashID = hash(_id);

	auto search = nodes.find(hashID);

	// if element with _id does not exist we add it

	if (search == nodes.end())
	{
		Node* newNode = new Node(_id);
		nodes.insert({ hashID, newNode });
	}
	// element with _id already existing
	else
	{
		std::cout << "Node with ID: \"" << _id << "\" already exist and is not added.\n";
		std::cout << _id;
	}
}


void Graph::deleteNode(std::string _id)
{
	unsigned int hashID = hash(_id);

	auto search = nodes.find(hashID);

	// there is element with _id and we need to delete it
	if (search != nodes.end())
	{
		//deleting node
		nodes.erase(hashID);


		//deleting vertices with this node
		for (auto it = nodes.begin(); it != nodes.end(); ++it)
		{
			it->second->vertices.erase(hashID);
		}
	}

	else
	{
		std::cout << "Node with ID: \"" << _id << "\" does not exist in the graph.\n";
	}
}


void Graph::BFS(const std::string& startNode, const std::string& endNode)
{
	algorithm<std::queue<std::vector<unsigned int>>>(startNode, endNode);
}

void Graph::dfsShortest(const std::string & startNode, const std::string & endNode)
{
	algorithm<Stack<std::vector<unsigned int>>>(startNode, endNode);
}
