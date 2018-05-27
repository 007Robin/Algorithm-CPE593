//Xin Song -- MergeSort
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

void Merge2array(vector<int>& res, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<int> v1, v2;
	for (int i = 0; i < n1; i++) {
		v1.push_back(res[left + i]);
	}
	for (int j = 0; j < n2; j++) {
		v2.push_back(res[mid + 1 + j]);
	}
	
	int i = 0; // Initial index of first subarray
	int j = 0; // Initial index of second subarray
	int k = left; // Initial index of merged subarray

	while (i < n1 && j < n2)
	{
		if (v1[i] <= v2[j])
		{
			res[k++] = v1[i++];
		}
		else
		{
			res[k++] = v2[j++];
		}
	}

	while(i < n1) {
		res[k++] = v1[i++];
	}
	while(j < n2) {
		res[k++] = v2[j++];
	}
}

void MergeSort(vector<int>& v, int left, int right) {
	if(left < right) {
		int mid = left + (right - left) / 2;
		MergeSort(v, left, mid);
		MergeSort(v, mid + 1, right);
		Merge2array(v, left, mid, right);
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
	for(auto i : v)
		cout << i << " ";
	cout << endl;
	
	return v;
}

int main() {
	vector<int> v = Loadfile("hw3.dat");
	MergeSort(v, 0, v.size() - 1);	
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
