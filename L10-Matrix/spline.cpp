//Xin Song -- cubic spline
//read data from file "hw9.dat"
//write data into "splineoutput.txt"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*
B C 0 0 ..   D0    =   Y0
A B C 0 ..   D1    =   Y1
  A B C ..   D2    =   Y2
	..
	 A B C
	   A B	 Dn-1  =   Yn-1
*/
vector<double> TriMatrix(vector<double> A, vector<double> B, vector<double> C, vector<double> Y, vector<double> D, int n) {
	//initilize D
	for(int i = 0; i < n; i++)
		D.push_back(0);
	
	int i;
	double temp;

	//first arow
	C[0] = C[0]/B[0];
	Y[0] = Y[0]/B[0];

	//center part 
	for(i = 1; i < n; i++) {
		temp = ((B[i] - A[i] * C[i-1]));
		C[i] = C[i] / temp;
		Y[i] = (Y[i] - A[i] * Y[i-1]) / temp;
	}

	//reverse to compute D
	D[n - 1] = Y[n - 1];
	for(i = n - 2; i >= 0; i--) {
		D[i] = Y[i] - C[i] * Y[i + 1];
	}

	return D;
}
class Spline{
private:
	int segment;
	vector<double> ai;
	vector<double> bi;
	vector<double> ci;
	vector<double> di;
	
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
	
public:
	Spline(vector<double> x, vector<double> y, int n) : segment(n-1) {

		//initialize A B C, Y
		B.push_back(2);
		Y.push_back(y[1] - y[0]);
		for(int i = 1; i < n - 2; i++) {
			A.push_back(1);
			B.push_back(4);
			C.push_back(1);
			Y.push_back(3*(y[i+1] - y[i-1]));
		}
		B.push_back(2);
		Y.push_back(y[n] - y[n-1]);
		
		//Tri Matrix to get D
		D = TriMatrix(A, B, C, Y, D, n);
		
		//get a, b, c, d
		for(int i = 0; i < n - 1; i++) {
			ai.push_back(y[i]);
			bi.push_back(D[i]);
			ci.push_back(3*(y[i+1] - y[i]) - 2*D[i] - D[i+1]);
			di.push_back(2*(y[i] - y[i+1]) + D[i] + D[i+1]);
		}
//		for(int i = 0; i < 3; i++)
//			cout << ai[i] << '\t' << bi[i] << '\t'  << ci[i] << '\t'  << di[i] << endl;
	}
	void output(vector<double> x) {
	/*	//print 
		cout << "segment" << '\t' << "t" << '\t' << "x" << '\t' << "y" << endl;
		double y = 0.0;
		for(int i = 0; i < segment; i++) {
			for(double t = 0.0; t <= 0.9; t += 0.1) {
				y = ai[i] + bi[i]*t + ci[i]*t*t + di[i]*t*t*t;
				cout << i << '\t' << t << '\t' << x[i] + (x[i+1]-x[i])*t << '\t' << y << endl;
			}
		}
*/
		ofstream out("splineoutput.txt");
		if(out) {
			out << "segment" << '\t' << "t" << '\t' << "x" << '\t' << "y" << endl;
			double y = 0.0;
			for(int i = 0; i < segment; i++) {
				for(double t = 0.0; t <= 0.9; t += 0.1) {
					y = ai[i] + bi[i]*t + ci[i]*t*t + di[i]*t*t*t;
					out << i << '\t' << t << '\t' << x[i] + (x[i+1]-x[i])*t << '\t' << y << endl;
				}
			}
			out.close();
		}
	}
};


int main() {
	ifstream ifs("hw9.dat");
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
	Spline s(xs, ys, n + 1);
	s.output(xs);
}
