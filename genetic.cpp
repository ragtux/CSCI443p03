//File: genetic.cpp
#include "EvoComp.hpp"

int main() {
	startup();

	//Gen size is maximum 1/5 the number of vertices in graph or 32 chromosomes, whichever is smaller. Always more than one.
	int gen_size = Vertices.size();
	if (gen_size < 2)
		gen_size = 2;
	if (gen_size > 32)
		gen_size = 32;

	Chromosome *old_gen[gen_size];
	Chromosome *new_gen[gen_size];

	//seed prototype/old generation with chromosomes that only have one vertex active
	for (int i = 0; i < gen_size; i++) {
		auto j = Vertices.begin();
		std::advance(j, rand() % Vertices.size());
		old_gen[i] = new Chromosome();
		old_gen[i]->active[j->first] = true;
		old_gen[i]->fitness++;
	}

	// Generation
	do {
		for (int i = 0; i < gen_size; i++) {
			if (((float) rand()) / RAND_MAX < 0.5) {
				//select one chrs and mutate;
				int j = rand() % gen_size;
				new_gen[i] = old_gen[j]->mutate();
			} else {
				//select two parents
				int p1 = rand() % gen_size, p2;
				do {
					p2 = rand() % gen_size;
				} while (p1 == p2);
				new_gen[i] = cross(old_gen[p1], old_gen[p2]);
			}
		}

		sort(new_gen, new_gen+gen_size, sort_by_fitness);

		//replace a maximum of 1/5 of old_gen with better fit from new_gen
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

		sort(old_gen, old_gen+gen_size, sort_by_fitness); 

		cout << "Best fitness is " << old_gen[gen_size-1]->fitness << ". Chrs is " << old_gen[gen_size-1] << endl;
	} while (old_gen[gen_size-1]->fitness != old_gen[0]->fitness);
}


