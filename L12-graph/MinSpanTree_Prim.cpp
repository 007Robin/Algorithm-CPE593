#include<iostream>
#include<queue>
#include<list>
#include<utility>
using namespace std;
# define INF 0x3f3f3f3f
/*
for Adjacency List
	Space complexity - O(E + V)
	Time complexity - O(E*logV)
for Matrix 
	Space, Time - O(V^2)
*/
/*
initiliza all vertices's keys as INF, every vertex's parent = -1
create PQ is a pair <weight = key, vertex>
initialize all vertices not part of MST(it make sure an already considered vertex is not in clude in PQ again)
insert src vertex into PQ, its key = 0

while PQ
	a. extractMin key as vertex u from PQ
	b. set inMST[u] = true
	c. look all adjactent vertex v of u
		if edge(u,v) < v's key && v not in MST
			update key[v]
			insert v into PQ
			parent[v] = u
print MST using parent array
*/
//O(E*logV)
class Graph{
	int V;
	list<pair<int, int>> * adj;
public:
	Graph(int V) : V(V) {
		adj = new list<pair<int, int>>[V];
	}
	void addEdge(int u, int v, int w) {
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	void primMST() {
		priority_queue< pair<int, int>, vector< pair<int, int>>, greater< pair<int,int>> > pq;
		//Every item of pq is a pair (weight, vertex). pair compare fisrt by their first members
		int src = 0;
		vector<int> key(V, INF);	//means weight 
		vector<int> parent(V, -1);
		vector<bool> inMST(V, false);
		//source itself key(weight) is 0
		pq.push({0, src});
		key[src] = 0;

		while(!pq.empty()) {
			int u = pq.top().second; 
			pq.pop();

			inMST[u] = true;
			
			//look through all adjactent vertex v of u
			list<pair<int, int>>::iterator i;
			for(i = adj[u].begin(); i != adj[u].end(); i++) {
				int v = (*i).first;
				int weight = (*i).second;

				if(inMST[v] == false && key[v] > weight) {
					key[v] = weight;
					pq.push({key[v], v});
					parent[v] = u;
				}
			}
		}

		//print
		for(int i = 1; i < V; i++) 
			cout << parent[i] << "--" << i << endl;
	}
};

int main() {
	int V = 9;
    Graph g(V);

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.primMST();

	return 0;
}
