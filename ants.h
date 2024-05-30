#ifndef ANT_H
#define ANT_H

#include "graph.h"
#include <vector>

using namespace std;

class Ant {
private:
    int currentCity, solutionDistance;
    vector<int> visitedCities;

public:
    Ant(int startCity); //ctor

    int getSolution(); //returns the ants solution

    vector<int> getSolutionPath(); //returns path ant took for its solution

    void moveToNextCity(Graph dist, Graph pher, double randomValue); //chooses next vertex to move to, factoring pheromone and distance, and makes selection using given random value

    void updatePheromoneTrail(Graph &pher); //adds pheromone to edges the ant visited

    void clearSolution(); //clears visitedCities and solutionDistance
};

#endif // ANT_H