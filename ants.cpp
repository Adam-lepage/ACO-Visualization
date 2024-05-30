#include "ants.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Ant::Ant(int startCity) {
    currentCity = startCity;
    solutionDistance = 0;
}

int Ant::getSolution() {
    return solutionDistance;
}

vector<int> Ant::getSolutionPath() {
    return visitedCities;
}


void Ant::moveToNextCity(Graph dist, Graph pher, double randomValue) {
    if (static_cast<int>(visitedCities.size()) == dist.getNumVertices()) clearSolution(); //if this ant is starting a new solution clear solution and visited city
    
    vector<double> prob; //holds probability for each next possible move
    vector<int> option; //holds options for next city to move to if that probability is chosen
    double totalProbability = 0.0;

    //calculate probabilities for neighboring unvisited cities
    for (int nextVertex = 0; nextVertex < dist.getNumVertices(); nextVertex++) {
        if (nextVertex != currentCity && find(visitedCities.begin(), visitedCities.end(), nextVertex) == visitedCities.end()) {
            prob.push_back((pher.getDistance(currentCity, nextVertex)) * (1.0 / (dist.getDistance(currentCity, nextVertex))));
            option.push_back(nextVertex);
            totalProbability += prob.at(prob.size() - 1);
        }
    }

    double overallProb = 0.0;
    int chosenCity = -1;
    
    //random probability edge selection
    for (long unsigned int i = 0; i < prob.size(); ++i) {
        overallProb += prob[i] / totalProbability;
        // cout  << "prob: " << prob[i] << endl << "overall: " << overallProb << " random val: " << randomValue << endl;
        if (randomValue <= overallProb) {
            chosenCity = option[i];
            break;
        }
    }

    if (overallProb == 0) chosenCity = visitedCities.front(); //if there are no cities left to visit we need to go back to starting point

    if (chosenCity == -1) throw out_of_range("No city found");

    //add chosen edge weight to solutionDistance 
    solutionDistance += dist.getDistance(currentCity, chosenCity);

    //add city ant was at to visitedCities and then change the current city to selected city
    visitedCities.push_back(currentCity);
    currentCity = chosenCity;
}

void Ant::updatePheromoneTrail(Graph &pher) {
    //update pheromone on all visited edges
    double pheromoneDeposit = 1.0 / solutionDistance;
    for (long unsigned int i = 0; i < visitedCities.size() - 1; i++) {
        int from = visitedCities[i];
        int to = visitedCities[i + 1];
        pher.adjustPheromone(from, to, pheromoneDeposit);
    }

    //update pheromone for the edge going back to start
    int last = visitedCities.back();
    int start = visitedCities.front();
    pher.adjustPheromone(last, start, pheromoneDeposit);
}

void Ant::clearSolution() {
    solutionDistance = 0;
    visitedCities.clear();
}