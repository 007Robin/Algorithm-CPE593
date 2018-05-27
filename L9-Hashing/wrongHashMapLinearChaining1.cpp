//Xin Song -- HashMapLinearChaining
#include<iostream>
#include<fstream>
#include "LinkedList1.hh"
using namespace std;

class HashMapLinearChaining {
private:
	class Bucket {
	public:
		string key;
		LinkedList1 val;
		bool present;

		Bucket() {
			present = false;
		}
	};
	Bucket* table;
	uint32_t size; //table size should be PRIME 31097
	int hist[52];
	int histsize = 52;
	int used;
	uint32_t hash(const string& key) {
		uint32_t sum = key.size();
		for(int i = 0; i < key.size(); i++) {
//			sum = (sum + key[i]) ^ (sum >> 13) ^ (sum << 17);
			sum = (sum << 5) + (sum >> 17) + key[i];
		}
		return sum % (size);
		//return sum % size;  size = 1024 (2 to 10) mod 1024 0...1023

	}
	void grow() {
		Bucket* old = table;
		int oldsize = size;
		size = size * 2 + 1;
		table = new Bucket[size];
		for(int i = 0; i < histsize; i++)
			hist[i] = 0;

		for(int i = 0; i < oldsize; ++i) {
			if(old[i].present)
				insert(old[i].key);
		}

		delete [] old;
	}
public:
	HashMapLinearChaining(uint32_t iniSize = 50000) : size(iniSize), used(0) {
		table = new Bucket[iniSize];
		for(int i = 0; i < histsize; i++)
			hist[i] = 0;
		
	}
	~HashMapLinearChaining() {
		delete [] table;
	}
	HashMapLinearChaining(const HashMapLinearChaining& orig) : size(orig.size) {
		table = new Bucket[size];
		for(int i = 0; i < size; i++) {
			if(orig.table[i].present)
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
		if(table[pos].present) {
			for(LinkedList1::Iterator i = table[pos].val; !i; ++i) {
				if(*i == key) {
					return true;
				}
			}
			return false;
		}
		return false;
	}

	//void insert(const string& key, const int v){
	void insert(const string& key){
//		if(used + used >= size)
//			grow();
		
		uint32_t pos = hash(key);
		if(table[pos].present) {
			int index = 1;
			for(LinkedList1::Iterator i = table[pos].val; !i; ++i) {
				index++;
				if(*i == key) {
					table[pos].val.remove(index);
					used--;
				}
			}
			table[pos].val.addFirst(key);
			used++;
		}
		else {
		//	if table[pos].present is false
			used++;
			table[pos].key = key;
			table[pos].val.addFirst(key);
			table[pos].present = true;		
		}
	}
	void displayHistogram() {
		hist[0] = 0;
		for(int i = 0; i < size; i++) {
			if(!table[i].present)
				hist[0]++;
			else {
				if(table[i].val.size() < 52)
					hist[table[i].val.size()]++;
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
		int count = 0;
		while(ifs >> word) {
//			cout << count++ << endl;
			m.insert(word);
		}
	}
	return;
}


int main() {
	HashMapLinearChaining m;
	load("dict.txt", m);
//	load("c++keywords.dat", m);	

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
	
	m.displayHistogram();

}
