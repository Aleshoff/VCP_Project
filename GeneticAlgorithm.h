#pragma once
#include"Graph.h"
#include<algorithm>
#include <cctype>
class GeneticAlgorithm
{
	int maxGeneration, populationSize, chromosomeSize;
	double mutationRate, crossoverRate;
	std::vector<std::string> population;
	Graph graph;
	double bestFitness = (double)INT_MAX;
	double alpha;
	std::string bestChromosome = "";


	double fitnessFunction(std::string chromosome);
	void crossover(std::string& child1, std::string& child2);
	void mutation(std::string& chromosome);
	void selection(const std::vector<std::string>& population, std::string& parent1, std::string& parent2);
	void rankedSelection(std::vector<std::string> &population, std::string& parent1, std::string& parent2);
	int partitionare(std::vector<std::string>& vect, int st, int dr);
	void quicksort(std::vector<std::string>& vect, int st, int dr);

public:
	GeneticAlgorithm(double mutationRate, double crossoverRate, int populationSize, int maxGeneration);
	void initialization(Graph graph);
	void evolution();
	double getBestFitness();
	std::string getBestChromosome();
	~GeneticAlgorithm();
};

