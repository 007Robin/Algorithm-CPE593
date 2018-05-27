//only edge sets E 
class BadEdgeListGraph {
	class Edge {
		int from;
		int to;
		double w;
	}
	List<Edge> edges;	//Storage: O(E) Ω(1)
public:
	bool isAdjacent(int i, int j) { … } //find out if i is adjacent to j, O(E) == O(V^2) Ω(1)
	bool[] adjacent(int i) { … } //find out the set of vertices connnected to i, O(E) == O(V^2)
}

/*
   the array of vertices must be there, so best case is V
   1 |-->
   2 |--> 3(w) -->
   3 |--> 4(w) --> 2(w)
   4 |--> 3(w)
*/
class EdgeListGraph {
	class Edge {
		int to;
		double w;
	}
	LinkedList<Edge>[] v;	//Storage: O(E) Ω(V)
public:
	bool isAdjacent(int i, int j) { … } //O(V)	Ω(1)
	bool[] adjacent(int i) { … } // O(V)		Ω(1)
}

/*
              to
        1	1	INF	1
from 	1	1	1	INF
		INF	1	1	1
		1	INF	1	1
*/
class MatrixGraph {
	double [] w;
	int V;
	//Space complexity: O(E) = O(V^2)      Ω(V^2)		= Θ(V^2)
public:
	bool isAdjacent(int i, int j) { return !isInf(w[i * V + j]); } //O(1)
	/*
	//if is non-directed graph, store only half the matrix
	isAdjacent(int from,  int to)   //O(1)
		if from < to
			return isAdajacent(to, from)
		return w[from][to]
	end
	*/
	bool[] adjacent(int v) { … } // O(V) Ω(V)
}

