//File: evolutionary.cpp
#include "EvoComp.hpp"

int main(int argc, char **argv) {
	startup();

	//Gen size is maximum 1/5 the number of vertices in graph or 32 chromosomes, whichever is smaller. Always more than one.
	const int gen_size = VERT_NO;
	if (argc != 2) {
		printf("Need to specific degree constraint");
		exit(1);
	} else {
		sscanf(argv[1], "%d", &degree); 
	}

	array<Chromosome *, gen_size> old_gen;
	array<Chromosome *, (const int) (gen_size*0.9)> new_gen;

	//seed prototype/old generation with chromosomes
	for (int i = 0; i < gen_size; i++) {
		old_gen[i] = new Chromosome();
		iota(old_gen[i]->permutation.begin(), old_gen[i]->permutation.end(), 0);
		random_shuffle(old_gen[i]->permutation.begin(), old_gen[i]->permutation.end());
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

		//replace 90 percent of old_gen with new_gen
		for (int i = 0; i < gen_size * 0.9; i++) {
			delete old_gen[i];
			old_gen[i] = new_gen[i];
			new_gen[i] = NULL;
		}

		sort(begin(old_gen), end(old_gen), sort_by_fitness); 

		cout << "Best fitness is " << old_gen[gen_size-1]->fitness << ". Chrs is " << old_gen[gen_size-1] << endl;
	} while (old_gen[gen_size-1]->fitness != old_gen[0]->fitness);
}


