-I have implemented a seperate script ("convert.cpp") that given .tsp files from the website https://www.math.uwaterloo.ca/tsp/vlsi/index.html ...
 will output the traveling salesman problem in the format my algorithm accepts. More details on how to use the script are commented on the file

-note the files named input are actually the matrix, run with the .in files in tests folder as follows:
 ./tsp_solver < tests/t01.in

Input files expect the following format {
[<string> name of input file with adjacency matrix] (format for this file shown below)
[<int> city for ants to start at (0 <= n < numberOfVertices)]
[<int> number of iterations to run for (n > 0)]
[<int> number of ants (n > 0)]
[<int> seed for random number generator (use -1 for no seed, otherwise n >= 0)]
[<double> pheromone evaporation rate (0 <= n < 1)]
}

-We use -1 to indicate edges that do not exist in the adjacency matrix

-The number of rows and columns must equal the single integer given on the first line

-Use commas to seperate each value (no commas on first line or at the end of a line)

Example of a valid input file {
5
-1, 1, 1, 1, 1
1, -1, 1, 1, 1
1, 1, -1, 1, 1
1, 1, 1, -1, 1
1, 1, 1, 1, -1
}

-In this example graph each node is connected to every other node (except for itself) with a weight of 1