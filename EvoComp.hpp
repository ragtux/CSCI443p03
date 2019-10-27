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
		void evalFitness();

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

		uint32_t permutation[VERT_NO];
		uint32_t fitness;
};

Chromosome::Chromosome() {
}

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
	temp->evalFitness();

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

void Chromosome::evalFitness() {
	int degree = 0;
	for (uint16_t i = 0; i < VERT_NO - 1; i++) {
		//fitness += weight[permutation[i]][permutation[i+1]];
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

	FILE *infile = fopen("testfile", "r");
	//check for file errs here

	for (uint16_t i = 0; i < VERT_NO; i++) {
		for (uint16_t j = i + 1; j < VERT_NO; j++) {
			if (!feof(infile)) {
				fscanf(infile, "%"SCNu16, weight[j][i]);
				weight[i][j] = weight[j][i];
			}
			//weight[i][j] = weight[j][i] = (uint16_t) rand();
		}
	}
}

