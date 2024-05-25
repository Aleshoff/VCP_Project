#include "Graph.h"

Graph::Graph()
{
	numberOfEdges = 0;	
}

void Graph::readGraph(std::string fileName)
{
	std::ifstream in(fileName);
	in >> verticesNumber;
	edges = new std::list<int>[verticesNumber+1];
	while (!in.eof())
	{
		int from, to;
		in >> from >> to;
		addEdge(from, to);
	}
}

void Graph::addEdge(int from, int to)
{
	
	edges[from].push_back(to); 
	edges[to].push_back(from);
	numberOfEdges += 1;
}

int Graph::getSize()
{
	return verticesNumber;
}

int Graph::getNumberOfEdges()
{
	return numberOfEdges;
}

int Graph::numberOfUncoveredEdges(std::string chromosome)
{
	int count = 0;
	std::unordered_set<int> covered;

	for (int i = 0; i < chromosome.size(); ++i)
	{
		if (chromosome[i] == '1')
		{
			covered.insert(i + 1);
			std::list<int>::iterator iter;
			for (iter = edges[i + 1].begin(); iter != edges[i + 1].end(); ++iter)
			{
				int temp = *iter;
				if (covered.find(temp) == covered.end())
					count++;
			}
		}
	}
	return numberOfEdges - count;
}

Graph::~Graph()
{
}
