#include<iostream>
#include<stack>
#include<vector>
#include<list>
using namespace std;

class Graph{
	int V;		//Number of vertice
	list<pair<int, double>>* adj;			//point to an array cotaining all adjacent vertice
public:
	Graph(int V) : V(V) {
		adj = new list<pair<int, double>>[V];
	}
	void addEdge(int i, int j, double w) {
		adj[i].push_back({j,w});
	}
	vector<pair<int, int>> getAllEdge() {
		vector<pair<int, int>> Es;
		for(int i = 0; i < V; i++) {
			list<pair<int, double>>::iterator iter;
			for(iter = adj[i].begin(); iter != adj[i].end(); ++iter) {
				Es.push_back({i, *iter.first});
			}
		}
		return Es;
	}

	//O(V * E), Space is O(V)
	//all shortest path is O(v^2 * E) = O(V^4)
	void getShortestPath(int start, int end) {
		// Step 1: Initialize distances from src to all other vertices as INFINITE
		vector<int> dist(V, INT_MAX);
		dist[start] = 0;
		
		vector<pair<int, int>> Es = getAllEdge();
		
		// Step 2: Relax all edges |V| - 1 times. A simple shortest 
		// path from src to any other vertex can have at-most |V| - 1 edges
		for(int v = 0; v < V - 1; v++) {
			//for each edge e
			for(auto e = Es.begin(); e != Es.end(); e++) {
				int u = e.fisrt; 
				int v = e.second;
		 		if(dist[u] + e.weight < dist[v] && dist[u] != INT_MAX) {
					dist[v] = dist[u] + e.weight;
				}
			}
		}

		// Step 3: check for negative-weight cycles.  The above step 
		// guarantees shortest distances if graph doesn't contain 
		// negative weight cycle.  If we get a shorter path, then there
		// is a cycle.
		for(auto e : Es) {
			int u = e.fisrt; 
			int v = e.second;
			if(dist[u] + e.weight < dist[v] && dist[u] != INT_MAX) {
				throw "Graph contains negative weight cycle";
			}
		}
	}
};
/*
 0|--3(8)--1(4)--2(5)
 1|--2(-3)
 2|--4(4)
 3|--4(2)
 4|--3(1)
*/
int main()
{
	// Create a graph given in the above diagram
	Graph graph(5);
	graph.addEdge(0, 3, 8);
	graph.addEdge(0, 1, 4);
	graph.addEdge(0, 2, 5);
	graph.addEdge(1, 2, -3);
	graph.addEdge(2, 4, 4);
	graph.addEdge(3, 4, 2);
	graph.addEdge(4, 3, 1);
	return 0;
}
