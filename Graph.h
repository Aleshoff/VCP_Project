#pragma once
#include <list>
#include <vector>
#include <iostream>
#include<fstream>
#include<unordered_set>
#include<string>

class Graph
{
    int verticesNumber;
    int numberOfEdges;
    std::list<int>* edges;  
    void addEdge(int, int);

public:
    Graph();
    void readGraph(std::string);
    int getSize();
    int getNumberOfEdges();
    int numberOfUncoveredEdges(std::string);
    ~Graph();
};

