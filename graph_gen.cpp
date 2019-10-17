#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

bool contains(vector<array<int,2>> &v, array<int,2> arr) {
	return (std::find(v.begin(), v.end(), arr) != v.end()) ? true : false;
}

int main (int argc, char **argv) {
	srand(time(NULL));
	int nodes = atoi(argv[1]);
	vector<array<int,2>> edges;
	edges.push_back({0,1});
	cout << edges[0][0] << " " << edges[0][1] << endl;

	for (int i = 2; i < nodes; i++) {
		int j = rand() % i;
		edges.push_back({i, j});
		cout << i << " " << j << endl;
	}

	int limit = rand() % ((nodes * (nodes-1))/2 - edges.size());
	for (int i = 0; i < limit; i++) {
		int j, k;
		do {
			j = rand() % nodes;
			k = rand() % nodes;
			if (j < k) swap(j, k);
		} while (contains(edges, {j, k}));
		edges.push_back({j, k});
		cout << j << " " << k << endl;
	}
	
	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i][0] << " " << edges[i][1] << endl;
	}
}
