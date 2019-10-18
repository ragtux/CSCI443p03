//File: heuristic.cpp
#include "EvoComp.hpp"

struct count {
	int id;
	int count;
};

bool sort_by_count (struct count x, struct count y) { return (x.count < y.count);}

int main () {
	startup();
	vector<struct count> edge_count;
	
	Chromosome *heur = new Chromosome();
	for (map<int,Vertex>::iterator i = Vertices.begin(); i != Vertices.end(); i++) {
		struct count j;
		j.id = i->first;
		j.count = i->second.neigh.size();
		edge_count.push_back(j);
	}
	cout << endl;

	sort(edge_count.begin(), edge_count.end(), sort_by_count);

	for (unsigned int i = 0; i < edge_count.size(); i++) {
		//cout << "(" << edge_count[i].id << ", " << edge_count[i].count << ") ";
		heur->add(edge_count[i].id);
	}

	cout << "Heuristic fitness is " << heur->fitness << endl;
}
