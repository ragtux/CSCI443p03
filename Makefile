
graph_gen:
	g++ -std=c++11 graph_gen.cpp -o graph_gen

evo:
	g++ -Wall -g -DVERT_NO=${VERT_NO} evolutionary.cpp -o evolutionary 

heur:
	g++ -Wall -g -DVERT_NO=${VERT_NO} heuristic.cpp -o heuristic
