//File: EvoComp.hpp
#include <iostream>
#include <algorithm>
#include <array>
#include <ctime>
#include <map>
#include <numeric>
#include <vector>
#include <cinttypes>

using namespace std;

uint16_t weight[VERT_NO][VERT_NO];

//TODO: overloaded comparison operator for fitness?
class Chromosome {
	public:
		Chromosome();
		Chromosome(array<uint32_t, VERT_NO>);
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

		array<uint32_t, VERT_NO> permutation;
		uint32_t fitness;
};

Chromosome::Chromosome() {
}

Chromosome::Chromosome(array<uint32_t, VERT_NO> permut) {
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
	Chromosome *temp = new Chromosome();
	int p1 = VERT_NO / 3, p2 = p1 * 2;
	vector<uint32_t> pool(c2->permutation.begin(), c2->permutation.end());

	for (int i = p1; i < p2; i++) {
		temp->permutation[i] = c1->permutation[i];	
		pool.erase(remove(pool.begin(), pool.end(), c1->permutation[i]), pool.end());
	}

	for (int i = p2; i != p1; i=(i+1)%VERT_NO) {
		temp->permutation[i] = pool[0]; pool.erase(pool.begin());
	}
	temp->evalFitness();
	return temp;
}

void Chromosome::evalFitness() {
	int degree = 0;
	uint16_t edge_num[VERT_NO] = {0};
	vector<uint16_t> pool;
	for (uint16_t i = 0; i < VERT_NO - 1; i++) {
		edge_num[i]++;
		uint16_t min_weight = weight[permutation[i]][permutation[i+1]];
		for (uint16_t j = 0; j < i; j++) {
			//TODO: need to also check that adding edge doesn't violate degree constraint
			if (weight[permutation[j]][permutation[i+1]] < min_weight) {
				min_weight = weight[permutation[j]][permutation[i+1]];
			}
		}
		fitness += min_weight;
		//hide edges that would violate degree constraint
		//make vector/map of verts with only one edge, and make sure nothing is added to those verts when the degree limit is reached
		//choose lightest that connects vert i+1 to the current tree without pushing degree past limit
	}
}

void Chromosome::print() {
	for (int i = 0; i < VERT_NO; i++) {
		cout << permutation[i] << "-";
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
				fscanf(infile, "%" SCNu16, &(weight[j][i]));
				weight[i][j] = weight[j][i];
			}
			//weight[i][j] = weight[j][i] = (uint16_t) rand();
		}
	}
}

int get_parent(array<Chromosome *, VERT_NO> gen) {
	uint16_t fitness = -1;
	int v = 0;
	for (int i = 0; i < 2; i++) {
		int temp = rand() % VERT_NO;
		if (gen[temp]->fitness < fitness) {
			v = temp;
			fitness = gen[temp]->fitness;
		}
	}
	return v;
}
