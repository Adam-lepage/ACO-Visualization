#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Graph::Graph() {//used to declare distance adjacency matrix
    string filename;
    cin >> filename;
    ifstream inFS(filename);
    string currLine;

    if (!inFS.is_open()) {
        throw invalid_argument("File not found or cannot be opened.");
    }

    //declare matrix with the given number of vertices
    double value;
    int col, row = 0;
    getline(inFS, currLine);
    stringstream ss(currLine);
    ss >> value;
    numVertices = value;
    adjacencyMatrix = new double*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new double[numVertices];
        //initialize elements to 0
        for (int j = 0; j < numVertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
    
    //add the edge weights from given input file
    while (getline(inFS, currLine)) { 
        stringstream ss(currLine);
        col = 0;

        while (ss >> value) {
            adjacencyMatrix[row][col] = value;
            ++col;
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        
        if (col != numVertices) {
            cout << "given num of vertices: " << numVertices << " / number of columns: " << col << endl;
            throw invalid_argument("Incorrect input file format ");
        }

        ++row;
    }

    inFS.close();
}

Graph::Graph(int size, double pherEvap) { //used to declare pheromone adjacency matrix
    //declare matrix with the given number of vertices, weights start at 1
    numVertices = size;
    pherEvapRate = pherEvap;
    adjacencyMatrix = new double*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new double[numVertices];
        // Initialize all elements to 0
        for (int j = 0; j < numVertices; j++) {
            adjacencyMatrix[i][j] = 1;
        }
    }
}


void Graph::adjustPheromone(int source, int destination, double deposit) {
    //as long long as source and destination are in range add deposit to edge
    if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) { 
        adjacencyMatrix[source][destination] += deposit;
        adjacencyMatrix[destination][source] += deposit;
    } else {
        throw out_of_range("Invalid vertex index.");
    }
}

void Graph::evaporatePheromone() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j) (adjacencyMatrix[i][j] *= (1.0 - pherEvapRate));
        }
    }
}

void Graph::display() {
    cout << endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double Graph::getDistance(int source, int destination) {
    if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
        return adjacencyMatrix[source][destination];
    } else { //for debuging
        cout << "From: " << source << endl << " To: " << destination << endl << adjacencyMatrix[source][destination] << endl;
        display();
        throw out_of_range("Invalid vertex index.");
    }
}

int Graph::getNumVertices() {
    return numVertices;
}