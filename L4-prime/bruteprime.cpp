#include<iostream>
using namespace std;

// true means n is prime
//O(n) omega(1)
bool bruteForceIsPrime(uint64_t n) {
	//n = 2
	for(uint64_t i = 2; i < n; i++) {
		if(n % i == 0)
			return false;
	}
	return true;
}

//O(sqrt(n)) omega(1)
bool bruteForceIsPrime2(uint64_t n) {
	//n = 2,3,4
	for(uint64_t i = 2; i <= sqrt(n); i++) {
		if(n % i == 0)
			return false;
	}
	return true;
}

//O(n*sqrt(n)
uint64_t countPrime(uint64_t n) {
	uint64_t count = 0;
	for(uint64_t i = 2; i <= n; i++) {
		if(bruteForceIsPrime2(i))
			count++;
	}
	return count;
}

int main() {
	cout << bruteForceIsPrime(1000000000000000001) << endl;
	cout << countPrime(n) << endl;
	cout << bruteForceIsPrime2(1000000000000000001) << endl;
	cout << countPrime(n) << endl;
}
