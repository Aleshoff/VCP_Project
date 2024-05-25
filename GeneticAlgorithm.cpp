#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(double mutationRate, double crossoverRate, int populationSize, int maxGeneration)
{
	this->mutationRate = mutationRate;
	this->crossoverRate = crossoverRate;
	this->populationSize = populationSize;
	this->maxGeneration = maxGeneration;
	srand(time(0));
}

void GeneticAlgorithm::initialization(Graph graph)
{
	this->graph = graph;
	this->chromosomeSize = graph.getSize();
	this->alpha = 1;

	for (int i = 0; i < populationSize; ++i)
	{
		std::string chromosome = "";
		for (int j = 0; j < chromosomeSize; ++j)
		{
			chromosome += (rand() % 2) ? "1": "0";
		}
		population.push_back(chromosome);
	}
}

void GeneticAlgorithm::evolution()
{
	for (int i = 0; i < maxGeneration; ++i)
	{
		std::vector<std::string> newPopulation;
		for (int j = 0; j < populationSize; ++j)
		{
			int currentFitness = fitnessFunction(population[j]);
			if (currentFitness < bestFitness)
			{
				bestFitness = currentFitness;
				bestChromosome = population[j];
				//if (i % 10 == 0)
				//{
				//	std::cout << bestFitness << " " << graph.numberOfUncoveredEdges(population[j]) * alpha << std::endl;
				//}
			}
		}
		for (int j = 0; j < populationSize; ++j)
		{
			std::string parent1, parent2;
			//selection(population, parent1, parent2);
			rankedSelection(population, parent1, parent2);
			crossover(parent1, parent2);
			mutation(parent1);
			newPopulation.push_back(parent1);
		}
		population = newPopulation;
	}
}

double GeneticAlgorithm::getBestFitness()
{
	return bestFitness;
}

std::string GeneticAlgorithm::getBestChromosome()
{
	return bestChromosome;
}




double GeneticAlgorithm::fitnessFunction(std::string chromosome)
{
	int nodesCovered = 0;
	for (int i = 0; i < chromosomeSize; ++i)
	{
		if (chromosome[i] == '1')
			nodesCovered++;
	}
	return nodesCovered + alpha*graph.numberOfUncoveredEdges(chromosome);
}

void GeneticAlgorithm::crossover(std::string& child1, std::string& child2)
{
	if ((double)rand() / RAND_MAX < crossoverRate)
	{
		//int point = rand() % chromosomeSize;
		//std::string result1 = child1.substr(0, point) + child2.substr(point, chromosomeSize - point);
		//std::string result2 = child2.substr(0, point) + child1.substr(point, chromosomeSize - point);
		std::string result = "";
		for (int i = 0; i < chromosomeSize; ++i)
		{
			int temp = (child1[i] - 48) ^ (child2[i] - 48);
			result += (temp) ? "1" : "0";
		}

		child1 = result;
		//child2 = result2;
	}
}

void GeneticAlgorithm::mutation(std::string& chromosome)
{
	for (int i = 0; i < chromosomeSize; ++i)
	{
		if ((double)rand() / RAND_MAX < mutationRate)
		{
			if (chromosome[i] == '0')
				chromosome[i] = '1';
			else
				chromosome[i] = '0';
		}
	}
}

void GeneticAlgorithm::selection(const std::vector<std::string>& population, std::string& parent1, std::string& parent2)
{
	parent1 = population[rand() % populationSize];
	parent2 = population[rand() % populationSize];
}


int GeneticAlgorithm::partitionare(std::vector<std::string>& vect, int st, int dr)
{
	int pivot = (int)fitnessFunction(vect[dr]);
	int i = st - 1;
	for (int j = st; j < dr; j++)
	{
		if ((int)fitnessFunction(vect[j]) >= pivot)
		{
			i++;
			std::swap(vect[i], vect[j]);
		}
	}
	std::swap(vect[i + 1], vect[dr]);
	return i + 1;
}

void GeneticAlgorithm::quicksort(std::vector<std::string>& vect, int st, int dr)
{
	if (st < dr)
	{
		int poz_pivot = partitionare(vect, st, dr);
		quicksort(vect, st, poz_pivot - 1);
		quicksort(vect, poz_pivot + 1, dr);
	}
}


void GeneticAlgorithm::rankedSelection(std::vector<std::string>& population, std::string& parent1, std::string& parent2)
{
	std::vector<std::string> populationSort = population;
	quicksort(populationSort, 0, populationSort.size() - 1);


	parent1 = populationSort[rand() % populationSize/2];
	parent2 = populationSort[rand() % populationSize/2];

}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

