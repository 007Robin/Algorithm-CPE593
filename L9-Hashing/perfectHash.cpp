//Xin Song -- PerfectHash
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class PerfectHash {
private:
	vector<string>* table;
	uint32_t size; //table size should be PRIME 31097
	uint32_t hash(const string& key, int n) {
		uint32_t sum = key.size();
		for(int i = 0; i < key.size(); i++) {
			sum = (sum << 5) + (sum >> 17) + key[i];
		}
		return sum % n;

	}
public:
	PerfectHash(uint32_t iniSize = 1024) : size(iniSize) {
		table = new vector<string>[iniSize];
		load("dict1.txt");
//		load("c++keywords.dat");
	}
	void load(string filename){
		ifstream ifs(filename);
		if(ifs) {
			string word;
			while(ifs >> word) {
				add(word);
			}
		}
		return;
	}
	~PerfectHash() {
		delete [] table;
	}
	PerfectHash(const PerfectHash& orig) : size(orig.size) {
		table = new vector<string>[size];
		for(int i = 0; i < size; i++) {
			if(!orig.table[i].empty())
				table[i] = orig.table[i];
		}
	}
	PerfectHash& operator=(const PerfectHash& orig) {
		PerfectHash copy(orig);
		size = copy.size;
		swap(table, copy.table);
		return *this;
	}
	
	bool contain(const string& s) {
		uint32_t pos = hash(s, size); 
		if(!table[pos].empty()) {
			int key2 = hash(s, table[pos].size() );
			if(table[pos][key2].empty())
				return false;
			else if (table[pos][key2] == s)
				return true;
			return false;
		}
		return false;
	}

	void add(const string& s){
		uint32_t pos = hash(s, size);
		//if cur_space has >1 elements: 
		//copy old to temp, new a larger space, rehash, add.
		if(!table[pos].empty()) {
			vector<string> temp = table[pos];
			for(int i = 0; i < table[pos].size(); i++){
				temp[i] = table[pos][i];
			}
			//while space is not empty then rehash
			do {
				table[pos].resize(temp.size() + 1);
				for(int i = 0; i < temp.size(); i++) {
					int key2 = hash(temp[i], table[pos].size());
					if(table[pos][key2].empty()) {
						table[pos][key2] = temp[i];
					}
					else {
						table[pos].resize(temp.size() + 1);
						i = 0;
					}
				}
			}while(!table[pos][hash(s, table[pos].size())].empty());
			//if space is empty then add
			table[pos][hash(s, table[pos].size())] = s;
		}
		//directly add 1st element 
		else {
			table[pos].push_back(s);	
		}
	}

};


int main() {
	PerfectHash m;
	
	ifstream ifs("hw8.dat");
	if(ifs) {
		string s;
		while(ifs >> s) {
			if (m.contain(s))
				cout  << s << " found!\n";
			else
				cout << s << " not found!\n";
		}
	}
	

}
