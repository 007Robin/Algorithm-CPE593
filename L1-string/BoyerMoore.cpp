//Xin Song -- BoyerMoore
#include<iostream>
#include<vector>
using namespace std;

// fast single string search
bool BoyerMoore(string& search, string& target){
	int m = target.size();
	int n = search.size();
	vector<int> table(128, m);
	// traverse target from its back, fulfill the table
	for(int i = m - 2, j = 0; i >= 0; i--) {
			table[target[i]] = ++j;
	}
	// match begin at the last element both in target and search word
	// i -- target , j -- search
	int jump = 0;
	int i = m - 1, j = m - 1;
	while(j < n) {
		if(search[j] != target[i]) {
			jump = table[search[j]];
			j += jump;
			// if some match already occurs at the inside of target, but now dismatch occurs
			// reset i to target's back.
			if( i != m - 1) {
				i = m - 1;
			}
		}
		else{	
			if(i == 0) {
				return true;
				break;
			}
			j--; i--;
		}
	}
	return false;
}

int main(){
	string search = "This is my string";
	string target = "Ng";
	cout << BoyerMoore(search, target) << endl;

	string s = "here is a simple example";
	string t = "simple";
	int res = BoyerMoore(s, t);
	cout << res << endl;
	string s1 = "hello";
	string t1 = "ll";
	int res2 = BoyerMoore(s1, t1);
	cout << res2 << endl;
	return 0;

}
