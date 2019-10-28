#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>


using namespace std; 

// number of vertices in the graph 
const int VERT_NO = 50; 
int weight[VERT_NO][VERT_NO];

void startup()
{
	srand(time(NULL));

	FILE *infile = fopen("test.dat", "r");
	//check for file errs here

	for (int i = 0; i < VERT_NO; i++) 
	{
		for (int j = i + 1; j < VERT_NO; j++) 
		{
			if (!feof(infile))
			{
				fscanf(infile, "%i", &(weight[j][i]));
				weight[i][j] = weight[j][i];
			}
		}
	}

	int fclose (FILE * stream);
}

/* minKey finds the vertex with minimum key value, from 
 * the set of vertices NOT YET included in MST 
 */ 
int minKey(int key[], bool mstSet[]) 
{ 
	// Initialize min value 
	int min = INT_MAX, 
			  min_index; 

	for (int v = 0; v < VERT_NO; v++)
	{ 
		if (mstSet[v] == false && key[v] < min) 
			min = key[v], min_index = v; 
	}
	
	return min_index; 
} 

/* A utility function to print the constructed MST stored in parent[]*/ 
void printMST(int parent[], int graph[VERT_NO][VERT_NO]) 
{ 
	cout<<"Edge \tWeight\n"; 
	for (int i = 1; i < VERT_NO; i++) 
		cout << setw(2) << parent[i]<< " - " 
		<< setw(2) << i << " " 
		<< setw(2) << graph[i][parent[i]] <<" \n"; 
} 

/* Function to construct and print MST for a graph represented using 
adjacency matrix representation */
void primMST(int graph[VERT_NO][VERT_NO]) 
{ 
	int parent[VERT_NO]; 	 // Array to store constructed MST 
	int key[VERT_NO]; 	 // Key values used to pick minimum weight edge in cut 
	bool mstSet[VERT_NO];  // To represent set of vertices not yet included in MST 

	// Initialize all keys as INFINITE 
	for (int i = 0; i < VERT_NO; i++) {key[i] = INT_MAX, mstSet[i] = false;} 

	// Always include first 1st vertex in MST. 
	// Make key 0 so that this vertex is picked as first vertex. 
	key[0] = 0; 
	parent[0] = -1; // First node is always root of MST 

	// The MST will have V vertices 
	for (int count = 0; count < VERT_NO - 1; count++) 
	{ 
		// Pick the minimum key vertex from the set of vertices not yet included in MST 
		int u = minKey(key, mstSet); 
		mstSet[u] = true;	// Add the picked vertex to the MST Set 

		/* Update key value and parent index of the adjacent vertices of
		 * the picked vertex. Consider only those vertices which are not 
		 * yet included in MST */ 
		for (int v = 0; v < VERT_NO; v++){
			// graph[u][v] is non zero only for adjacent vertices of m 
			// mstSet[v] is false for vertices not yet included in MST 
			// Update the key only if graph[u][v] is smaller than key[v] 
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
				parent[v] = u, key[v] = graph[u][v];
		} 
	} 

	// print the constructed MST 
	printMST(parent, graph); 
} 

int main(int argc, char **argv) 
{ 
	srand(time(NULL));
	startup();
	//sscanf(argv[1], "%d", degree);

	primMST(weight); 

	return 0; 
} 

