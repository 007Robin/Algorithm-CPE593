#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

// true means n is prime
//O(sqrt(n)) omega(1)
bool badisprime(uint64_t n) {
	//n = 2,3,4
	if(n < 2) return false;
	for(uint64_t i = 2; i <= sqrt(n); i++) {
		if(n % i == 0)
			return false;
	}
	return true;
}

//O(n*sqrt(n)
uint64_t badcountPrime(uint64_t n) {
	uint64_t count = 0;
	for(uint64_t i = 2; i <= n; i++) {
		if(badisprime(i))
			count++;
	}
	return count;
}
//O(n log(logn) )
uint64_t isPrime(uint64_t n) {
	if(n < 1) return false;
	vector<uint64_t> table(n, true);
	table[0] = false; //means at index 0, 1 is not prime

	for(uint64_t i = 3; i < n; i += 2) { //at index 3(4 Not Prime), index 5(6 Not Prime... pass all even.
		table[i] = false; //actuall is number 4, 6, 8 ...
	}
	for(uint64_t i = 3; i <= sqrt(n); i++) {
		if(table[i - 1]) {  //actuall is number 3, 5 , 7 ...
			for(uint64_t j = i*i; j < n; j += 2*i) 
				table[j - 1] = false;			
		}
	}
	return table[n - 1];
}

//O(n log(logn) ) omega(1)
uint64_t countPrime(uint64_t n) {
	//first all true, we then set notprime false
	vector<bool> num(n-1, true); 
	num[0] = false;
	
	for(uint64_t i = 2; i <= sqrt(n); i++) {
		if(num[i - 1]){ //if cur is a prime, we can jump to filt
			uint64_t jump = 0;
			if( i == 2) 
				jump = i;
			else 
				jump = 2*i;

			for(uint64_t j = i*i; j < n; j += jump) 
				num[j - 1] = false;
		}	
	}

	//now we have a prime table
	uint64_t count = 0;
	for( uint64_t i = 0; i < n - 1; i++) {
		if (num[i]) count++;
	}
	return count;
}

int main() {
//	cout << badisprime(1000000000000000001) << endl;
	for(int i = 0; i < 15 ; i++)
		cout << badisprime(i) << " ";
	cout << badcountPrime(100) << endl;
	//cout << isPrime(1000000000000000001) << endl;
	cout << '\n';
	for(int i = 0; i < 15 ; i++)
		cout << isPrime(i) << " ";
	cout << countPrime(100) << endl;
}
