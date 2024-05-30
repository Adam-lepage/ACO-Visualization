tsp_solver: main.o graph.o ants.o
	g++ -Wall -pedantic -g -o tsp_solver main.o graph.o ants.o

main.o: main.cpp graph.h ants.h
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp

graph.o: graph.cpp graph.h
	g++ -Wall -pedantic -g -std=c++11 -c graph.cpp

ants.o: ants.cpp ants.h
	g++ -Wall -pedantic -g -std=c++11 -c ants.cpp

clean:
	rm -rf main.o graph.o ants.o tsp_solver convert.o convert