
graph_gen:
	g++ -std=c++11 graph_gen.cpp -o graph_gen

genetic:
	g++ -Wall -g -DVERT_NO=${VERT_NO} genetic.cpp -o genetic
