//Xin Song -- InsertionSort
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

void InsertionSort(vector<int>& arr) {
	//insertion
	int i, key, j;
   	for (i = 1; i < arr.size(); i++)
	{
		key = arr[i];
       		j = i-1;
	       /* Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
	       while (j >= 0 && arr[j] > key)
	       {
		   arr[j+1] = arr[j];
		   j = j-1;
	       }
	       arr[j+1] = key;
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
	InsertionSort(v);	
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
