#include <iostream>
#include <cstdlib>
#include <random>
#include <algorithm>
using namespace std;

double f(double x) { return 8 - x * x; }

const double PHI = (1 + sqrt(5)) /2;

typedef double(*FuncOneVar)(double);
//double integrate(double (*f)(double), double a, double b) { //pointer to a function return 0;}
double goldenMean(FuncOneVar f, double L, double R) {
	double S = (R-L) / PHI;
	double x1 = R - S;
	double x2 = L + S;
	double y1 = f(x1);
	double y2 = f(x2);
	while (  abs(R - L) > 0.5 ) {
		if (y1 > y2) {
			R = x2;
			x2 = x1;
			y2 = y1;
			S = (R - L)/ PHI;
			x1 = R - S;
		} else if (y2 <= y1) {
			L = x1;
			x1 = x2;
			y1 = y2;
			S = (R - L) / PHI;
			x2 = L + S;
		}	
	}
	return y1 > y2 ? x1 : x2;

}

int main() {
	cout << goldenMean(f, -3.0, 4.0) << endl;
}
