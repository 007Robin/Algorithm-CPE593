#include<iostream>
#include<fstream>

class GraphMatrix {
	static constexpr BIG = 1e100;
	double *w;
	int v;
public:
	GraphMatrix(const char[] filename) {
		ifstream f(filename);
		f >> v;
		for(int i = 0; i < v; i++) {
			for(int j = 0; j < v; j++) 
				f >> w[i * v + j];
		}
		
	}
	~GraphMatrix() {
		delete [] w;
	}

	GraphMatrix(const GraphMatrix& orig) = delete;
	GraphMatrix& operator=(const GraphMatrix& orig) = delete;

	double adjacent(int i, int j) const {
		return w[i * v + j];
	}
	bool isAdjacent(int i, int j) {
		return w[i * v + j] == BIG;
	}

	void dfs(int v0) {
		bool visited[V] = {false};
		dfs(v0, visited);
	}

	void dfs(int v, bool visited[]) {
		cout << v;
		visited[v] = true;
		for(int v2 = 0; v2 < v; v2++) {
			if(isAdjacent(v, v2) && !visited[v2]) 
				dfs(v2, visited);
		}
	}
	//O(V^2)
	void dfsIterative(int v0) {
		stack<int> todo;
		todo.push(v0);
		bool visited[V] = {false};
		visited[v0] = true;

		while(!todo.empty()) { //O(V)
			int v = todo.top();
			cout << v;
			todo.pop();
			for(int v2 = 0; v2 < V; v2++) {  //O(V)
				if(isAdjacent(v, v2) && !visited[v2]) {
					todo.push(v2);
					visited[v2] = true;
				}
			}
			
		}


	}

	friend ostream& operator<<(ostream& s, const GraphMatrix& g) {
		for(int i = 0; i < g.v; i++) 
			for(int j = 0; j < g.v; j++) 
				cout << g.adjacent(i, j) << '\t';
			cout << '\n';
		return s;
	}
};

int main() {
	GraphMatrix g("graph.dat");
	cout << g << '\n';

	g.dfs(0);
	g.bfs(0);
}
