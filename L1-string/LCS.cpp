//Xin Song -- LCS
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

int LCS(string& s1, string& s2){
	int n = s1.size(), m = s2.size();
	vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
	for(int i = 0; i <= m; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(i == 0 || j == 0) 
				f[j][i] = 0;
			else if(s2[i - 1] != s1[j - 1])	
				f[j][i] = max(f[j - 1][i], f[j][i - 1]);
			else	
				f[j][i] = f[j - 1][i - 1] + 1;
		}
	}
	return f[n][m];
}

string loadFile(const char filename[]) {
	ifstream f(filename);
	string contents;
	// read the string
	string buf;
	if(f){
		while(getline(f, buf)){
			contents += buf;
		}
	} 
	return contents;
}

//enter "./LCS a.txt b.txt" in command to run this program.
int main(int argc, char* argv[]) {
	string a = loadFile(argv[1]);
	string b = loadFile(argv[2]);
	cout << LCS(a, b) << endl;
	return 0;
}
