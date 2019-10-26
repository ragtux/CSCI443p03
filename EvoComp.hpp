//File: EvoComp.hpp
#include <iostream>
#include <algorithm>
#include <array>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

uint16_t weight[VERT_NO][VERT_NO];

//TODO: overloaded comparison operator for fitness?
class Chromosome {
	public:
		Chromosome();
		Chromosome(map<int,bool>);
		Chromosome *mutate();
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

		//map<int,bool> active;
		uint32_t permutation[VERT_NO];
		uint32_t fitness;
};

/* Chromosome::Chromosome() {
	fitness = 0;
	for (std::map<int,Vertex>::iterator i = Vertices.begin(); i != Vertices.end(); i++) {
		active[i->first] = false;
	}
}
*/

Chromosome::Chromosome(uint32_t permut[VERT_NO]) {
	permutation = permut;
}

Chromosome *Chromosome::mutate() {
	Chromosome *temp = new Chromosome(permutation); temp->fitness = fitness;
	int i, j;
	
	do {
		i = rand() % VERT_NO;
		j = rand() % VERT_NO;
	} while (i == j);
	swap(temp->permutation[i], temp->permutation[j]);

	/*
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
	*/

	return temp;
}

Chromosome *cross (Chromosome *c1, Chromosome *c2) {
	Chromosome *temp = new Chromosome(); temp->fitness = fitness;
	int p1 = VERT_NO / 3, p2 = p1 * 2;
	vector<uint32_t> pool(c2->permutation, c2->permutation + VERT_NO);

	for (int i = p1; i < p2; i++) {
		temp->permutation[i] = c1->permutation[i];	
		pool.erase(remove(pool.begin(), pool.end(), c1->permutation[i]), pool.end());
	}

	for (int i = p2; i != p1; i=(i+1)%VERT_NO) {
		temp->permutation[i] = pool[0]; pool.erase(0);
	}
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
	/*FILE *infile = fopen("ARXIV_GeneralRelativity_QuantumCosmology_1993-2003.txt", "r");
	//check for file errs here

	while (!feof(infile)) {
		int v1, v2;
		fscanf(infile, "%d %d", &v1, &v2);
		Vertices[v1].id = v1;
		Vertices[v1].add(v2);
	}
	*/
	for (uint16_t i = 0; i < VERT_NO; i++) {
		for (uint16_t j = i + 1; j < VERT_NO; j++) {
			if (i == j)
				continue;
			weight[i][j] = weight[j][i] = (uint16_t) rand();
		}
	}
}
