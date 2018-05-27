#include <iostream>
using namespace std;

int main() {
	Matrix a(3,4,0.0);  // O(mn) = O(3*4)
	Matrix b(4,2,1.0); //O(n*p) = O(4*2);
	Matrix c = b; // make a copy O(np)
	Matrix d = a * b;  //O(mnp)
	Matrix e = a + a;  //O(mn)
	b(1,1) = 5.2; // calls operator()(int,int)
	cout << b(1,2); // calls operator()(int,int)const
	e = b;

	ifstream f("hw5.dat");
	Matrix A = Matrix::read(f);
	vector<double> B = read(A.getRows(), f);
	vector<double> x = solve(A, B);
	Matrix L, U;
	A.LU(L, U); //LU = A
	//just solve once, use L to compute answers

	//generalized least squares
	A.leastSquares(B);

	//QR Factorization
	//PCA Principle component analysis

	for (auto v : x) {
		cout << v << '\t';
	}
	cout << '\n';
	
	// automatically call destructor
	//~Matrix(); //O(1)
}
