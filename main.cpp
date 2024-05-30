#include "graph.h"
#include "ants.h"
#include <iostream>
#include <cstdlib>
#include <ctime> 

using namespace std;

int main() {
    //construct adjacency matrix that holds edge distances (This constructor also reads in adj. matrix input file)
    Graph dist;

    //initialize parameters
    int startingCity, numIterations, numAnts, rngSeed, numCities = dist.getNumVertices();
    double pherEvapRate;
    cin >> startingCity >> numIterations >> numAnts >> rngSeed >> pherEvapRate;

    //construct adjacency matrix that holds pheromones
    Graph pher(dist.getNumVertices(), pherEvapRate);

    //initialize seeded rng
    rngSeed == -1 ? srand(static_cast<unsigned>(time(nullptr))) : srand(rngSeed);

    //initialize ant colony
    vector<Ant> colony;
    for (int i = 0; i < numAnts; ++i) {
        colony.push_back(Ant(startingCity));
    }

    // Main loop for each time
    for (int time = 0; time < numIterations; time++) { //loop for each iteration
        cout << time << endl;
        for (long unsigned int i = 0; i < colony.size(); i++) { //loop for each ant in the colony
            Ant &ant = colony[i];
            for (int move = 0; move < numCities; move++) { //loop for ant to move over every vertex
                ant.moveToNextCity(dist, pher, static_cast<double>(rand()) / RAND_MAX);
            }
            ant.updatePheromoneTrail(pher); //lay pheromone on visited edges
        }
        pher.evaporatePheromone();
    }

    //find the best solution
    int solution, bestAnt = 0;
    vector<int> solutionPath;
    //loop over each ant to find the one with shortest solution distance
    for (long unsigned int i = 0; i < colony.size(); i++) {
        if (colony[i].getSolution() < colony[bestAnt].getSolution()) bestAnt = i;
    }
    solution = colony[bestAnt].getSolution();
    solutionPath = colony[bestAnt].getSolutionPath();
    
    //print best solution
    cout << "The best found solution is of length " << solution << ", which used the following path:" << endl;
    for (long unsigned int i = 0; i < solutionPath.size(); i++) {
        cout << i + 1 << ". " << solutionPath[i] << endl;
    }

    return 0;
}