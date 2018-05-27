#include<iostream>
#include<vector>
using namespace std;

#define V 4     // Number of vertices in the graph
#define INF 99999

void pathPrint(int u, int v, int path[][V]) {
	vector<int> ans;
	if (path[u][v] == -1) {
		cout << "[]";
		return ;
	}
	cout << u << " ";
	while(u != v) {
		u = path[u][v];
		ans.push_back(u);
	}
	for(auto i : ans) 
		cout << i <<  " ";
	cout << endl;
}


// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
//Time complexity - O(v^3)
//Space complexity - O(V^2)
void floydWarshall (int graph[][V])
{
	int dist[V][V], i, j, k;
	int path[V][V];

	//Initialize the solution matrix same as input graph matrix. 
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++) {
			dist[i][j] = graph[i][j];
			if(dist[i][j] != INF && i != j)
				path[i][j] = j;
			else 
				path[i][j] = -1;
		}

	//pick k as an intermediate vertex
		// Pick i all vertices as source one by one
			// Pick j all vertices as destination for the above picked source
	for (k = 0; k < V; k++)	{
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of dist[i][j]
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
	//print dist
	cout <<"dist matrix : \n"
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF\t";
			else
				cout << dist[i][j] << '\t';
		}
		cout << endl;
	}

	cout <<"path matrix : \n"
	//print path
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (path[i][j] == -1)
				cout << "INF\t";
			else
				cout << path[i][j] << '\t';
		}
		cout << endl;
	}
	//print path from 0 to 3
	pathPrint(0, 3, path);
}

int main()
{
	/* graph
	         10
	   (0)------->(3)
	     |         /|\
	   5 |          |
	     |          | 1
	    \|/         |
	    (1)------->(2)
	          3           */
	int graph[V][V] = { {0,   5,  INF, 10},
						{INF, 0,   3, INF},
						{INF, INF, 0,   1},
						{INF, INF, INF, 0}
	};

	floydWarshall(graph);
	return 0;
}
