//Xin Song -- HeapSort
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;



void maxheap(vector<int>& nums, int idx, int heapsize) {
	int max = idx;
	int lch = idx * 2 + 1, rch = idx * 2 + 2;
	if(lch < heapsize && nums[lch] > nums[max]) {
		max = lch;
	}
	if(rch < heapsize && nums[rch] > nums[max]) {
		max = rch;
	}
	if(max != idx) {
		swap(nums[idx], nums[max]);
		maxheap(nums, max, heapsize);
	}
}

void HeapSort(vector<int>& nums){
	int	heapsize = nums.size();
	// start at last element's father
	for(int i = heapsize/2 - 1; i >= 0; i--){
		maxheap(nums, i, heapsize);
	}

	for(int i = heapsize - 1; i >= 0; i--) {
		swap(nums[0], nums[i]);
		maxheap(nums, 0, i - 1);
	}
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
	v.erase(v.begin());
	return v;
}

int main() {
	vector<int> v = Loadfile("hw3.dat");
	HeapSort(v);	
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
