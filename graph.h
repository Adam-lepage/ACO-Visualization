#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph {
private:
    int numVertices;
    double **adjacencyMatrix;
    double pherEvapRate;

public:
    Graph();         //used to construct DISTANCE adjacency matrix (this is also where we read the input file)

    Graph(int size, double pherEvap); //used to construct PHEROMONE adjacency matrix

    void adjustPheromone(int source, int destination, double weight); //adds the pheromone to an individual edge

    void evaporatePheromone(); //evaporates given fraction of pheromone off of all edges when called

    void display(); //displays adjacency matrix

    double getDistance(int source, int destination); //gets the edge weight from given source to destination
    
    int getNumVertices(); //returns numVertices
};

#endif // GRAPH_H