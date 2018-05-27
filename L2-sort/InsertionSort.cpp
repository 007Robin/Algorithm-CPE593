//Xin Song -- InsertionSort
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

void InsertionSort(vector<int>& v) {
	//number of elements
	int n = v[0];
	//insertion
	for(int i = 2; i <= n; ++i) {
		int temp = v[i];
		int j;
		for(j = i; j >= 1 && v[j - 1] > temp; --j) 
			v[j] = v[j - 1];
		v[j] = temp;
	}
	v.erase(v.begin());
}

//read from file
vector<int> Loadfile(const string& filename) {
	// store all elements in a vector
	ifstream ifs(filename);
	vector<int> v{};
	if(ifs) {
		int n = 0;
		while(ifs >> n)
			v.push_back(n);
	}
	return v;
}

int main() {
	vector<int> v = Loadfile("hw3.dat");
	InsertionSort(v);	
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
