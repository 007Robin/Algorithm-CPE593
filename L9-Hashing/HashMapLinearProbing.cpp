//Xin Song -- HashMapLinearProbing
//hash function cite: http://burtleburtle.net/bob/hash/integer.html 
#include<iostream>
using namespace std;

class HashMapLinearProbing {
private:
	class Bucket {
	public:
		uint32_t key;
		int val;
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
	//
	uint32_t hash(uint32_t key) {
		key ^= (key >> 20) ^ (key >> 12);
		key = key ^ (key >> 7) ^ (key >> 4);
		return key % size;

	}
	void grow() {
		Bucket* old = table;
		int oldsize = size;
		size = size * 2 + 1;
		table = new Bucket[size];
		
		for(int i = 0; i < 52; i++) hist[i] = 0;
		
		for(int i = 0; i < oldsize; i++) {
			if(old[i].present) {
				add(old[i].key);
			}		
		}
		delete[] old;
	}
public:
	HashMapLinearProbing(uint32_t iniSize = 1024) : size(iniSize), used(0) {
		table = new Bucket[iniSize];
		for(int i = 0; i < histsize; i++)
			hist[i] = 0;
		
	}
	~HashMapLinearProbing() {
		delete [] table;
	}
	HashMapLinearProbing(const HashMapLinearProbing& orig) : size(orig.size) {
		table = new Bucket[size];
		for(int i = 0; i < size; i++) {
			if(orig.table[i].present)
				table[i] = orig.table[i];
		}
	}
	HashMapLinearProbing& operator=(const HashMapLinearProbing& orig) {
		HashMapLinearProbing copy(orig);
		size = copy.size;
		swap(table, copy.table);
		return *this;
	}
/*	//remove() function
	bool remove(const uint32_t& key) {
		uint32_t pos = hash(key); 
		
		while(table[pos].present) {
			if(table[pos].key == key) {
				table[pos].key = 0;
				table[pos].val = 0;
				table[pos].present = false;	
					//rehash everyone follows 
					//until next 0
				return true;
			}
			pos = (pos + 1) % size; // mod size(size should be power of 2)
		}
		return false;
	}
*/

	//find() function	
	Bucket& operator[] (const uint32_t& key) {
		uint32_t pos = hash(key); 
		
		while(table[pos].present) {
			if(table[pos].key == key) 
				return table[pos];
			pos = (pos + 1) % size; // mod size(size should be power of 2)
		}
		return table[pos];
	}
	//add() 
	void add(const uint32_t& key){
		if(used + used >= size) 
			grow();

		uint32_t pos = hash(key);
		int count = 1;	
		while(table[pos].present) {
			if(table[pos].key == key) {
				table[pos].val = key;
				if(count > 49)
					count = 50;
				hist[count]++;
				return;
			}
			count++;
//			pos = (pos + 1) & (size - 1); // mod size(size should be power of 2)
			pos = (pos + 1) % size;
		}

	//	if table[pos].present is false
		if(count > 49)
			count = 50;
		hist[count]++;
		table[pos].key = key;
		table[pos].val = key;
		table[pos].present = true;		
		used++;
	}
	void displayHistogram() {
		hist[0] = size - used;
		for(int i = 0; i < histsize - 1; i++) {
			cout << i << "\t" << hist[i] << endl;
		}
		cout << ">50" << "\t" << hist[histsize - 1] << endl;
	}

};

int main() {
	int n;
	cin >> n;
	HashMapLinearProbing m;
	for (int i = 0; i < n; i++)
		m.add(i);
	//for (int i = 0; i < n; i++)
	//	    m.add(rand());
	m.displayHistogram();
/*
	HashMapLinearProbing m;
	m.add(1);
	m.add(9);
	m.add(10);
	m.add(17);
	m.displayHistogram();
*/

}
