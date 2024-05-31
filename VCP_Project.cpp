#include "Graph.h"
#include "GeneticAlgorithm.h"
#include"PSOAlgorithm.h"
#include<chrono>

int main()
{
    Graph g;
    srand(time(0));
    GeneticAlgorithm ga(0.05, 0.7, 100, 50);
    PSOAlgorithm pso(0.9, 2, 2, 50, 50);
    
    //g.readGraph("Test.txt");
    g.readGraph("Proximity.txt");
    //g.readGraph("EuroRoad.txt");
    
    ga.initialization(g);
    pso.initialization(g);

    auto started = std::chrono::high_resolution_clock::now();
    ga.evolution();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
    std::cout << std::endl;
    std::cout << ga.getBestChromosome() << "\n" << ga.getBestFitness() << " " << g.numberOfUncoveredEdges(ga.getBestChromosome()) << std::endl;
    
    started = std::chrono::high_resolution_clock::now();
    pso.runPSO();
    done = std::chrono::high_resolution_clock::now();
   
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
    std::cout << std::endl;
    std::cout << pso.getGlobalBestPosition() << "\n" << pso.getGlobalBestFitness() << " " << g.numberOfUncoveredEdges(pso.getGlobalBestPosition()) << std::endl;
}


