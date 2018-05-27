#include<iostream>
#include<queue>
#include<vector>
#include<list>
using namespace std;

//BFS
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
	void enterBFS(int v) {
		vector<bool> visited(V, false);
		queue<int> q;
		q.push(v);
		visited[v] = true;
		BFS(visited, q);
	}
	void BFS(vector<bool> visited, queue<int> q) {
		if(q.empty()) return;

		int v = q.front();
		q.pop();
		cout << v << " ";
		//Recur for all never visited adjacent vertices 
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i) {
			if(!visited[*i]) {
				q.push(*i);
				visited[*i] = true;
			}
		}
		BFS(visited, q);
	}
	
	//iterative BFS, queue
	void iterativeBFS(int v) {
		vector<bool> visited(V, false);
		queue<int> q;
		q.push(v);
		visited[v] = true;

		while(!q.empty()) {
			v = q.front(); q.pop();
			cout << v << " ";
			//for all never visited adjacent vertices 
			list<int>::iterator i;
			for(i = adj[v].begin(); i != adj[v].end(); ++i) {
				if(!visited[*i]) {
					q.push(*i);
					visited[*i] = true;
				}
			}
		}
	}
	//IsConnected
	bool isconnected(int v) {
		vector<bool> visited(V, false);
		queue<int> q;
		q.push(v);
		visited[v] = true;
		int count = 1;

		while(!q.empty()) {
			v = q.front(); q.pop();
			//for all never visited adjacent vertices 
			list<int>::iterator i;
			for(i = adj[v].begin(); i != adj[v].end(); ++i) {
				if(!visited[*i]) {
					q.push(*i);
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

	cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
	g.enterBFS(2);
	cout << "\nIterative Breadth First Traversal (starting from vertex 2) \n";
	g.iterativeBFS(2);
	cout << "\nisConnected graph " << g.isconnected(2);
	return 0;
}
