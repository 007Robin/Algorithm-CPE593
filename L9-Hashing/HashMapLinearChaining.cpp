//Xin Song -- HashMapLinearChaining
#include<iostream>
#include<fstream>
#include<forward_list>
using namespace std;

class HashMapLinearChaining {
private:
	forward_list<string>* table;
	uint32_t size; //table size should be PRIME 31097
	int hist[52];
	int histsize = 52;
	uint32_t hash(const string& key) {
		uint32_t sum = key.size();
		for(int i = 0; i < key.size(); i++) {
			sum = (sum << 5) + (sum >> 17) + key[i];
		}
		return sum % size;

	}

public:
	HashMapLinearChaining(uint32_t iniSize = 50000) : size(iniSize) {
		table = new forward_list<string>[iniSize];
		for(int i = 0; i < histsize; i++)
			hist[i] = 0;
		
	}
	~HashMapLinearChaining() {
		delete [] table;
	}
	HashMapLinearChaining(const HashMapLinearChaining& orig) : size(orig.size) {
		table = new forward_list<string>[size];
		for(int i = 0; i < size; i++) {
			if(!orig.table[i].empty())
				table[i] = orig.table[i];
		}
	}
	HashMapLinearChaining& operator=(const HashMapLinearChaining& orig) {
		HashMapLinearChaining copy(orig);
		size = copy.size;
		swap(table, copy.table);
		return *this;
	}
	
	bool contain(const string& key) {
		uint32_t pos = hash(key); 
		
		if(!table[pos].empty()) {
			for(auto i = table[pos].begin(); i != table[pos].end(); ++i) {
				if(*i == key) {
					return true;
				}
			}
			return false;
		}
		return false;
	}

	void insert(const string& key){
		uint32_t pos = hash(key);
		//insert >1 elements
		if(!table[pos].empty()) {
			for(auto i = table[pos].begin(); i != table[pos].end(); ++i) {
				if(*i == key) {
					table[pos].remove(key);
				}
			}
			table[pos].push_front(key);
		}
		//directly add 1st element
		else {
			table[pos].push_front(key);	
		}
	}
	void displayHistogram() {
		hist[0] = 0;
		for(int i = 0; i < size; i++) {
			if(table[i].empty())
				hist[0]++;
			else {
				int k = 0;
				for(auto j = table[i].begin(); j != table[i].end(); ++j, k++) 
					;
				if(k < 52)
					hist[k]++;
				else
					hist[51]++;
			}
		}
		for(int i = 0; i < 51; i++) 
			cout << i << "\t" << hist[i] << endl;
		cout << ">50" << "\t" << hist[51] << endl;
	}

};

void load(string filename, HashMapLinearChaining& m){
	ifstream ifs(filename);
	if(ifs) {
		string word;
		//int count = 0;
		while(ifs >> word) {
			m.insert(word);
		}
	}
	return;
}


int main() {
	HashMapLinearChaining m;
	load("dict.txt", m);
//	load("c++keywords.dat", m);	

	m.displayHistogram();
	
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
