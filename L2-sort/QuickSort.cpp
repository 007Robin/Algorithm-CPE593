//Xin Song -- QuickSort
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

//get a pivot, sort once
void SortOnce(vector<int>&v, int beg, int end) {
	// get a pivot
	if(beg >= end) return ;
	int pos	= rand() % (end - beg) + beg;
	swap(v[pos], v[end]);
	int pivot = v[end];
	
	int start = beg;
	int p = beg;
	while(p < end) {
		if(v[p] < pivot) {
			swap(v[start], v[p]);
			start++;
		}
		p++;
	}
	swap(v[start], v[p]);
	
	SortOnce(v, beg, start - 1);
	SortOnce(v, start + 1, end);
}
void QuickSort(vector<int>& v) {
	// number of elements
	int n = v[0];
	v.erase(v.begin());
	SortOnce(v, 0, v.size() - 1);	
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
	QuickSort(v);	
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
