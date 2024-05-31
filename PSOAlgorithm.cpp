#include "PSOAlgorithm.h"

PSOAlgorithm::PSOAlgorithm(double w, double c1, double c2, int swarmSize, int maxIter)
{
	this->w = w;
	this->c1 = c1;
	this->c2 = c2;
	this->swarmSize = swarmSize;
	this->maxIter = maxIter;
	this->alpha = 1.0;
	this->globalBestPosition = "";
	this->globalBestFitness = (double)INT_MAX;
}

double PSOAlgorithm::fitnessFunction(Particle particle)
{
	int nodesCovered = 0;
	for (int i = 0; i < particleSize; ++i)
	{
		if (particle.position[i] == '1')
			nodesCovered++;
	}
	return nodesCovered + alpha * graph.numberOfUncoveredEdges(particle.position);
}


void PSOAlgorithm::updateVelocity(Particle& particle)
{
	double r1 = (double)rand() / RAND_MAX;
	double r2 = (double)rand() / RAND_MAX;

	for (int i = 0; i < particleSize; ++i)
	{
		particle.velocity[i] = w * particle.velocity[i] + c1 * r1 * (((double)particle.bestPosition[i] - 48) - ((double)particle.position[i] - 48)) + c2 * r2 * (((double)globalBestPosition[i] - 48) - ((double)particle.position[i] - 48));
		//std::cout << particle.velocity[i] << std::endl;
	}
}


void PSOAlgorithm::runPSO()
{
	for (int i = 0; i < maxIter; ++i)
	{
		for (Particle& particle : swarm)
		{
			double currentFitness = fitnessFunction(particle);
			if (currentFitness < particle.bestFitness)
			{
				particle.bestFitness = currentFitness;
				particle.bestPosition = particle.position;
			}
			if (currentFitness < globalBestFitness)
			{
				globalBestFitness = currentFitness;
				globalBestPosition = particle.position;
			}
		}
		for (Particle& particle : swarm)
		{
			updateVelocity(particle);
			updatePosition(particle);
		}
	}
}

std::string PSOAlgorithm::getGlobalBestPosition()
{
	return globalBestPosition;
}

double PSOAlgorithm::getGlobalBestFitness()
{
	return globalBestFitness;
}



void PSOAlgorithm::updatePosition(Particle& particle)
{
	for (int i = 0; i < particleSize; ++i)
	{
		double temp = ((double)particle.position[i] - 48) + particle.velocity[i];
		//std::cout << temp << std::endl;
		if (temp < 1 && temp > 0)
			particle.position[i] = '1';
		else 
			particle.position[i] = '0';
	}
}

void PSOAlgorithm::initialization(Graph graph)
{
	this->graph = graph;
	this->particleSize = graph.getSize();

	for (int i = 0; i < swarmSize; ++i)
	{
		Particle particle;
		particle.position = "";
		for (int j = 0; j < particleSize; ++j)
		{
			particle.position += (rand() % 2) ? "1" : "0";
		}
		particle.bestPosition = particle.position;
		particle.bestFitness = fitnessFunction(particle);
		for (int j = 0; j < particleSize; ++j)
		{
			double temp = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
			particle.velocity.push_back(temp);
		}
		swarm.push_back(particle);
	}
}
