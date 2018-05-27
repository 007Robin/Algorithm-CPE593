//Xin Song
#include<iostream>
#include<vector>
using namespace std;

// naive string matching
bool naive(string& search, string& target){
	int n = search.size(), m = target.size();
	int i = 0, j = 0;
	while(i < n) {
		if(search[i] == target[j]) {
			if(j == m - 1) {
				return true;
				break;
			}
			i++; j++;
		}
		else{
			if(j != 0 && j == m - 1)	
				i--;
			j = 0;
			i++;
		}
	}
	return false;
}

int main(){
	//string search = "This is my string";
	//string target = "isis";
	string search = "iiis";
	string target = "is";
	cout << naive(search, target) << endl;

	string s = "here is a simple example";
	string t = "simple";
	int res = naive(s, t);
	cout << res << endl;
	return 0;

}
