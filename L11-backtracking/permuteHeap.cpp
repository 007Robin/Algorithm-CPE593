//permute -- time complextity O(N!) space complexity O(N)
#include<iostream>
using namespace std;
class Permute{
private:
	int* p;	
	int N;
public:
	Permute(int l[], int numbers) : p(l), N(numbers) {
/*
		cout << "heap permute" << endl;
		heaps(N - 1);
	*/
		cout << "simple permute" << endl;
		simple(N - 1);
	}
	
	void print() {
		for(int i = 0; i < N; i++)
			cout << p[i];
		cout << '\n';
	}

	void heaps(int N) { 
		if (N == 0) { 
			print(); 
			return; 
		}
		for (int c = 0; c <= N; c++) {
			heaps(N - 1);
			swap( (N % 2 == 0 ? p[0] : p[c]), p[N]);
		}
	}

	void simple(int N) {
		if (N == 0) { 
			print(); 
			return; 
		}
		for (int c = 0; c <= N; c++) {
			swap(p[c], p[N]);
			simple(N - 1);
			swap(p[c], p[N]);
		}

	}
};

int main() {
	int x[] = {1,2,3,4};
	Permute p(x, 4);

}
