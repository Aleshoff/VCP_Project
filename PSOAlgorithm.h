#pragma once
#include"Particle.h"
#include"Graph.h"
#include<cmath>

class PSOAlgorithm
{
	std::vector<Particle> swarm;
	int swarmSize, maxIter, particleSize;
	double w, c1, c2, globalBestFitness;
	double alpha;
	std::string globalBestPosition;
	Graph graph;

	double fitnessFunction(Particle particle);
	void updateVelocity(Particle& particle);
	void updatePosition(Particle& particle);

public:
	PSOAlgorithm(double w, double c1, double c2, int swarmSize, int maxIter);
	void initialization(Graph graph);
	void runPSO();
	std::string getGlobalBestPosition();
	double getGlobalBestFitness();
};

