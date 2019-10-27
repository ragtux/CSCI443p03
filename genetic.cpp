//File: genetic.cpp
#include "EvoComp.hpp"

int main() {
	startup();

	//Gen size is maximum 1/5 the number of vertices in graph or 32 chromosomes, whichever is smaller. Always more than one.
	const int gen_size = VERT_NO;

	array<Chromosome *, gen_size> old_gen;
	array<Chromosome *, (const int) (gen_size*0.9)> new_gen;

	//seed prototype/old generation with chromosomes
	for (int i = 0; i < gen_size; i++) {
		old_gen[i] = new Chromosome();
		iota(old_gen[i]->permutation.begin(), old_gen[i]->permutation.end(), 1);
		random_shuffle(begin(old_gen), end(old_gen));
		old_gen[i]->evalFitness();
	}

	// Generation
	do {
		for (int i = 0; i < gen_size * 0.9; i++) {
			int p1 = get_parent(old_gen);
			if (((float) rand()) / RAND_MAX < 0.3) {
				//select one chrs and mutate;
				new_gen[i] = old_gen[p1]->mutate();
			} else {
				//select two parents
				int p2 = get_parent(old_gen);
				new_gen[i] = cross(old_gen[p1], old_gen[p2]);
			}
		}

		//replace a maximum of 1/5 of old_gen with better fit from new_gen
		/*
		for (int i = 0, j = gen_size-1; i <= gen_size/5; i++, j--) {
			if (*(new_gen[j]) > *(old_gen[i])) {
				delete old_gen[i];
				old_gen[i] = new_gen[j];
				new_gen[j] = NULL;
			}
		}

		for (int i = 0; i < gen_size; i++) {
			if (new_gen[i])
				delete new_gen[i];
		}
		*/

		sort(begin(old_gen), end(old_gen), sort_by_fitness); 

		cout << "Best fitness is " << old_gen[gen_size-1]->fitness << ". Chrs is " << old_gen[gen_size-1] << endl;
	} while (old_gen[gen_size-1]->fitness != old_gen[0]->fitness);
}


