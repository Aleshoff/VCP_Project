#include "Graph.h"
#include "GeneticAlgorithm.h"
#include<chrono>

int main()
{
    Graph g;
    srand(time(0));
    GeneticAlgorithm ga(0.01, 0.7, 30, 50);
    //g.readGraph("Test.txt");
    //g.readGraph("Proximity.txt");

    g.readGraph("EuroRoad.txt");
    ga.initialization(g);
    //std::string str = "01011101";
    //std::cout << g.getSize() << std::endl;
    //std::cout << g.numberOfUncoveredEdges(str);

    auto started = std::chrono::high_resolution_clock::now();
    ga.evolution();
    auto done = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
    std::cout << std::endl;
    std::cout << ga.getBestChromosome() << "\n" << ga.getBestFitness() << " " << g.numberOfUncoveredEdges(ga.getBestChromosome()) << std::endl;
    
}


