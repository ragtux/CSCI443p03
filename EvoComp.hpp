//File: EvoComp.hpp
#include <iostream>
#include <algorithm>
#include <array>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

class Vertex {
	public:
		void add(int);
		bool isNeigh(int);
		int id;
		vector<int> neigh {};
};

map<int, Vertex> Vertices;

void Vertex::add(int v) {
	if (find(neigh.begin(), neigh.end(), v) == neigh.end()) {
		neigh.push_back(v);
		Vertices[v].add(id);
	}
}

//TODO: overloaded comparison operator for fitness?
class Chromosome {
	public:
		Chromosome();
		Chromosome(map<int,bool>);
		Chromosome *mutate();
		bool add(int);
		void del(int);
		void print();

		inline bool operator == (const Chromosome &b) const
		{
			return fitness == b.fitness;
		}
		inline bool operator < (const Chromosome &b) const
		{
			return fitness < b.fitness;
		}
		inline bool operator > (const Chromosome &b) const
		{
			return fitness > b.fitness;
		}

		map<int,bool> active;
		uint32_t fitness;
};

Chromosome::Chromosome() {
	fitness = 0;
	for (std::map<int,Vertex>::iterator i = Vertices.begin(); i != Vertices.end(); i++) {
		active[i->first] = false;
	}
}

Chromosome::Chromosome(map<int,bool> chrs) {
	active = chrs;
}

Chromosome *Chromosome::mutate() {
	Chromosome *temp = new Chromosome(active); temp->fitness = fitness;

	for (int j = 0; j < 10; j++) {
		auto i  = temp->active.begin();
		std::advance(i, rand() % temp->active.size());
		float r = ((float) rand())/((float) RAND_MAX);
		if (i->second && r < 0.1) {
			temp->del(i->first);
			break;
		} else if (!(i->second) && r >= 0.1) {
			temp->add(i->first);
			break;
		}
	}

	return temp;
}

Chromosome *cross (Chromosome *c1, Chromosome *c2) {
	Chromosome *temp = new Chromosome();
	for (map<int,bool>::iterator i = c1->active.begin(), j = c2->active.begin(); i != c1->active.end(); i++, j++) {
		if (i->second | j->second) {
			temp->add(i->first);
		}
	}
	return temp;
}

bool Chromosome::add(int n) {
	for (unsigned int i = 0; i < Vertices[n].neigh.size(); i++) {
		int neighbor = Vertices[n].neigh[i];
		if (active[neighbor]) {
			return false;
		}
	}
	active[n] = true;
	fitness++;
	return true;
}

void Chromosome::del(int n) {
	active[n] = false;
	fitness--;
}

void Chromosome::print() {
	for (map<int,bool>::iterator i = active.begin(); i != active.end(); i++) {
		cout << "{" << i->first << "," << i->second << "} ";
	}
	cout << endl;
}

bool sort_by_fitness (Chromosome* x, Chromosome* y) {
	return (x->fitness < y->fitness);
}

void startup() {
	srand(time(NULL));
	FILE *infile = fopen("ARXIV_GeneralRelativity_QuantumCosmology_1993-2003.txt", "r");
	//check for file errs here

	while (!feof(infile)) {
		int v1, v2;
		fscanf(infile, "%d %d", &v1, &v2);
		Vertices[v1].id = v1;
		Vertices[v1].add(v2);
	}

}
