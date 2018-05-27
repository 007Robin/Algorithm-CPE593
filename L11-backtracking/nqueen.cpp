/*
   	Xin Song -- N Queen Problem
	N queen问题：剪枝不剪枝时间复杂度分别是O(n^n)与O(n!)
	Space complexity O(n*n)
*/
#include<iostream>
#include<vector>
using namespace std;

class NQueen{
public:
	struct Position {
		int row, col;
		Position(int r, int c) : row(r), col(c) {}
		friend ostream& operator <<(ostream& s, const Position& p) {
			s << "(" << p.row << ", "<< p.col <<  ") ";
			return s;
		}
	};
	vector<Position> positions;
	int n;
public:
	NQueen(int n) : n(n) {
		for(int i = 0; i < n; i++) 
			positions.push_back(Position(0,0));
	}
	~NQueen() {
	}
	vector<Position> enterNQueenProblem(int n) {
		bool hasSolution = SolveNQueenProblem(n, 0, positions);
		if(hasSolution) 
			return positions;
		else 
			return vector<Position>();
	}
	//row from 0 to n
	bool SolveNQueenProblem(int n, int row, vector<Position>& positions) {
		if(n == row) {
			return true;
		}
		
		int col;
		for(col = 0; col < n; col++) {
			bool flag = true;

			//check row, col, diagnal.
			for(int queen = 0; queen < row; queen++) {
				if(positions[queen].col == col || positions[queen].row - positions[queen].col == row - col || positions[queen].row + positions[queen].col == row + col) {
					flag = false;
					break;
				}
			}

			if(flag) {
				positions[row] = Position(row, col);
				if(SolveNQueenProblem(n, row + 1, positions)) {
					return true;
				}
			}
		}
		return false;
	}
};

int main() {
	NQueen s(4);
	vector<NQueen::Position> positions = s.enterNQueenProblem(4);
	for(auto i : positions)
		cout << i << " ";
	cout << endl;
}
