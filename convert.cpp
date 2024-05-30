#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

//converts tsp from the following website into the format my algorithm takes: https://www.math.uwaterloo.ca/tsp/vlsi/index.html
//Compile with: g++ convert.cpp -Wall -g -pedantic -o convert
//To use just run the file and have it write out to the empty input file you want the converted file to go into, example: ./convert > inputFile1
//Then all you have to do is type the name of the file from that website you want to be converted example: xqf131.tsp
//Now inputFile1 will be ready to use for algorithm

int main() {
    string filename;
    cin >> filename;
    ifstream inFS(filename);
    if (!inFS.is_open()) {
        throw invalid_argument("File not found or cannot be opened.");
    }
    string currLine;
    //ignore first 8 lines of comments and headers
    for (int i = 0; i < 8; i++) getline(inFS, currLine);

    int value1, value2, value3;
    vector<int> x;
    vector<int> y;

    //read in file values
    while (inFS >> value1 >> value2 >> value3) {
        x.push_back(value2);
        y.push_back(value3);
    }

    //write into the given input file 
    cout << x.size() << endl;
    int currentX, currentY;
    double distance;
    for (long unsigned int i = 0; i < x.size(); i++) {
        for (long unsigned int j = 0; j < y.size(); j++) {
            if (i == j) distance = -1; //from a node to itself weight is -1
            else {
                currentX = x[i];
                currentY = y[i];
                distance = sqrt(pow((x[j] - currentX),2) + pow((y[j] - currentY), 2)); //use pythagoreans theorem to find distance between 2 coordinates
            }
            cout << distance;
            if (j != y.size() - 1) cout << ", ";
        }
        if (i != x.size() - 1) cout << endl;
    }


    inFS.close();
    return 0;
}
