//Xin Song -- cubic spline
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<double> TriMatrix(vector<double> A, vector<double> B, vector<double> C, vector<double> Y, vector<double> D, int n) {
	for(int i = 0; i < n; i++)
		D.push_back(0);
	
	int i;
	double temp;

	C[0] = C[0]/B[0];
	Y[0] = Y[0]/B[0];

	for(i = 1; i < n; i++) {
		temp = ((B[i] - A[i] * C[i-1]));
		C[i] = C[i] / temp;
		Y[i] = (Y[i] - A[i] * Y[i-1]) / temp;
	}

	//Y[n - 1]
	D[n - 1] = Y[n - 1];
	for(i = n - 2; i >= 0; i--) {
		D[i] = Y[i] - C[i] * Y[i + 1];
	}

	return D;
}
class Spline{
private:
	double* yset;
	int n;
	vector<double> ai;
	vector<double> bi;
	vector<double> ci;
	vector<double> di;
	
	vector<double> h;
	/*
	B C 0 0 ..   D0    =   Y0
	A B C 0 ..   D1    =   Y1
	  A B C ..   D2    =   Y2
		..
		 A B C
		   A B	 Dn-1  =   Yn-1
	   */
	vector<double> A;
	vector<double> B;
	vector<double> C;
	vector<double> D;
	vector<double> Y;
	
	vector<double> M;
public:
	Spline(vector<double> x, vector<double> y, int n) {
		//compute h[i]
		for(int i = 0; i < n - 1; i++)
			h.push_back(x[i + 1] - x[i]);

		//initialize A B C, Y
		for(int i = 0; i < n - 3; i++) {
			A.push_back(h[i]);
			B.push_back(2*(h[i] + h[i+1]));
			C.push_back(h[i+1]);
			Y.push_back(6 * ((x[n + i + 2] - x[n + i + 1]) / h[i + 1] - (x[n + i + 1] - x[n + i]) / h[i]));
		}
		//Tri Matrix to get D
		D = TriMatrix(A, B, C, Y, D, n-3);
		
		//compute M
		M.push_back(0);
		for(int i = 1; i < n - 1; i++) {
			M.push_back(D[i]);
		}
		M.push_back(0);

		//get a, b, c, d
		for(int i = 0; i < n - 1; i++) {
			ai.push_back(x[n+i]);
			bi.push_back((x[n + i + 1] - x[n + i]) / h[i] - (2 * h[i] * M[i] + h[i] * M[i + 1]) / 6);
			ci.push_back(M[i] / 2);
			di.push_back((M[i + 1] - M[i]) / (6 * h[i]));
		}
//		*yset = ai[step] + bi[step]*(x - x[step]) + ci[step] * (x - x[step]) * (x - x[step]) + di[step] * (x - x[step]) * (x - x[step]) * (x - x[step]);
	}

};


int main() {
	ifstream ifs("splinehwinput.dat");
	vector<double> xs;
	vector<double> ys;
	int n = 0;
	if(ifs) {
		ifs >> n;
		double x, y = 0;
		for(int i = 0; i <= n; i++) {
			ifs >> x >> y;
			xs.push_back(x);
			ys.push_back(y);
		}
	}
	Spline s(xs, ys, n+1);
}
