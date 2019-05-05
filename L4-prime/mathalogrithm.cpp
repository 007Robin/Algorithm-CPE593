#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

//O(logn)
int gcd(int a, int b) { 
	return if (b == 0) ? a: gcd(b, a%b);
}
int gcd2(int a, int b) { 
	while(b != 0) {
		int temp = a; 
		a = b; 
		b = b % temp;	
	}
	return a;
}

//O(logn)
int lcm(int a, int b) { 
	return a * b / gcd(a, b);
}

//O(logn)
double power(double x, int n) { 
	if(n == 0) return 1;
	double half = power(x, n/2);
	if(n % 2 == 0) 
		return half*half;
	else 
		return half*half*x;
}

//O(logn)
double powermod(double x, int n, double m) {
	if(n == 0) return 1;
	double half = powermod(x, n/2, m);
	if( n % 2 == 0) 
		return fmod(half * half, m);
	else 
		return fmod(half * half * x, m);
}

//O(logn)
double power2(double x,int n) {
	double ans = 1;
	while(n > 0) {
		if(n % 2 != 0) 
			ans = ans * x;
		x = x * x;
		n = n / 2;
	}
	return ans;
}

//O(logn)
double powermod2(double x,int n, double m) {
	double ans = 1;
	while(n > 0) {
		if(n % 2 != 0) 
			ans = fmod(ans * x, m);
		x = fmod(x * x, m);
		n = n / 2;
	}
	return ans;
}

//O(nlogn)
bool Fermat(int p, int k) {
	for(int i = 1; i < k; i++) {
		int a = rand() % (p-1) + 2;	//random number from 2 to p-1
		if(powermod2(a, p-1, p) != 1) {
			return false;
		}
	}
	return true;
}

//O(nlogn)
bool MillerRabin(int n, int k) { 
	//n-1 = 2^s * d;
	int s = 0;
	while(((n - 1) & (1 << s)) == 0) { s++; }
	double d = (n-1) / power(2, s);
	
	for(int i = 1; i < k; i++) {
		int a = rand() % (n-1) + 2;
		double x = powermod(a, d, n);
		if ( x == 1 || x == n - 1) 
			continue;
		for(int j = 1; j < s-1; j++) {
			x = powermod(x, 2, n);
			if( x == 1) 
				return false; //composite
			if( x == n-1)
				continue;
			return false;
		}
	}
	return true;
}

int main() {
	cout << gcd (3025, 1025) << endl;
	cout << lcm (12, 24) << endl;
	cout << power(2, 100) << endl;
	cout << powermod(2, 100, 7) << endl;
	cout << power2(2, 100) << endl;
	cout << powermod2(2, 100, 7) << endl;
	cout << Fermat(10, 3) << endl;
	cout <<	MillerRabin(221, 3) << endl;
}
