//Xin Song -- QuickSort
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
//O(n log n) 
//步骤解释： https://docs.google.com/document/d/1qYlmVRfTxceHM6tBQjUbWOQnUslhx4qnJ8TzU1OVMBI/edit?usp=sharing
//get a pivot, sort once, 经过一次sort划出，左边是比pivot小的一些数，右边是比pivot大的数
void SortOnce(vector<int>&v, int beg, int end) {
	// get a pivot
	if(beg >= end) return ;
	int pos	= rand() % (end - beg) + beg;
	swap(v[pos], v[end]);
	int pivot = v[end];
	
	int start = beg;
	int p = beg;
	while(p < end) {
		//用p辅助遍历，遇到比pivot小的数，swap v[p]与v[start], start总track小的数
		if(v[p] < pivot) {
			swap(v[start], v[p]);
			start++;
		}
		p++;
	}
	//最后相当于swap v[start]与pivot，相当于把pivot放在了它应该在的位置，在这个位置左边都比它小，右边都比它大
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
