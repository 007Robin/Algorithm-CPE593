#include<iostream>
#include<stack>
#include<vector>
#include<list>
using namespace std;

//DFS
//Time Complexity: O(V+E) where V is number of vertices in the graph and E is number of edges in the graph.
//Complexity is O(V^2) or Ω(V) if sparse, not using matrix
class Graph{
	int V;		//Number of vertice
	list<int>* adj;			//point to an array cotaining all adjacent vertice
public:
	Graph(int V) : V(V) {
		adj = new list<int>[V];
	}
	void addEdge(int v, int w) {
		adj[v].push_back(w);
	}
	//recursive
	void enterDFS(int v) {
		vector<bool> visited(V, false);
		DFS(v, visited);
	}
	void DFS(int v, vector<bool> visited) {
		visited[v] = true;
		cout << v << " ";
		//Recur for all never visited adjacent vertices 
		list<int>::iterator i;
		//O(V), Ω(1)
		for(i = adj[v].begin(); i != adj[v].end(); ++i) {
			if(!visited[*i]) {
				DFS(*i, visited);
			}
		}
	}
	
	//stack
	void iterativeDFS(int v) {
		vector<bool> visited(V, false);
		stack<int> s;
		s.push(v);
		visited[v] = true;

		while(!s.empty()) {
			v = s.top(); s.pop();
			cout << v << " ";
			//for all never visited adjacent vertices 
			list<int>::iterator i;
			for(i = adj[v].begin(); i != adj[v].end(); ++i) {
				if(!visited[*i]) {
					s.push(*i);
					visited[*i] = true;
				}
			}
		}
	}
	//isconnected O(V^2)
	bool isconnected(int v) {
		vector<bool> visited(V, false);
		stack<int> s;
		s.push(v);
		visited[v] = true;
		int count = 1;

		while(!s.empty()) {
			v = s.top(); s.pop();
			//for all never visited adjacent vertices 
			list<int>::iterator i;
			for(i = adj[v].begin(); i != adj[v].end(); ++i) {
				if(!visited[*i]) {
					s.push(*i);
					visited[*i] = true;
					count++;
				}
			}
		}
		return count == V;
	}
};
/*
   0 --------->  1
 |   ^        /
 |   |       /
 |   |      /
 |   |     /       __
 |   |    V       |  |
 V   2   --------> 3 V

 0|--1--2
 1|--2
 2|--0--3
 3|--3

*/
int main()
{
	// Create a graph given in the above diagram
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Following is Depth First Traversal (starting from vertex 2) \n";
	g.enterDFS(2);
	cout << "\nIterative Depth First Traversal (starting from vertex 2) \n";
	g.iterativeDFS(2);
	cout << "\nIsConnected graph " << g.isconnected(2) << endl; 
	return 0;
}
