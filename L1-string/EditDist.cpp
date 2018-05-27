//Xin Song -- EditDist
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

int EditDist(string& word1, string& word2){
	int n = word1.size(); 
	int m = word2.size();
	vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
	for(int i = 0; i <= n; ++i)
		f[i][0] = i;
	for(int i = 0; i <= m; ++i)
		f[0][i] = i;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(word1[i - 1] == word2[j - 1]) {
				f[i][j] = f[i - 1][j - 1];
			}
			else {
				f[i][j] = min(min(f[i - 1][j - 1] + 1, f[i][j - 1] + 1), f[i - 1][j] + 1);
			}
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

//enter "./EditDist a.txt b.txt" in command to run this program.
int main(int argc, char* argv[]) {
	string a = loadFile(argv[1]);
	string b = loadFile(argv[2]);
	cout << EditDist(a, b) << endl;
	return 0;
}
