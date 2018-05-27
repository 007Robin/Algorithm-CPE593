#include<iostream>
#include<string>
using namespace std;

class HashMapLinearProbing {
private:
	class Bucket {
	public:
		string key;
		int val;
		bool present;

		Bucket() {
			present = false;
		}
	};
	Bucket* table;
	uint32_t size; //table size should be PRIME 31097
	uint32_t hash(const string& key) {
		uint32_t sum = key.size();
		for(int i = 0; i < key.size(); i++) 
			sum = (sum << 5) + (sum >> 17) + key[i];
		return sum & (size - 1);
		//return sum % size;  size = 1024 (2 to 10) mod 1024 0...1023
	}
public:
	HashMapLinearProbing(uint32_t iniSize = 1024) : size(iniSize) {
		table = new Bucket[iniSize];
	
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
/*	
		if(this != &orig ) {
			delete [] table;
			size = orig.size;
			table = new Bucket[size];
			for(int i = 0; i < size; i++) {
				if(orig.table[i].present)
					table[i] = orig.table[i];
			}
		}
		return *this;
*/
		HashMapLinearProbing copy(orig);
		size = copy.size;
		swap(table, copy.table);
	
		return *this;
	}

	//operator[] (const char* s) {//only work for string
	Bucket& operator[] (const String& key) {
		uint32_t pos = hash(key); 
		
		while(table[pos].present) {
			if(table[pos].key == key) 
				return table[pos];
			pos = (pos + 1) & (size - 1); // mod size(size should be power of 2)
		}
	//used++ 
		return table[pos];
	//	if(pos >= size)  pos = 1;
	}
};

int main() {
	HashMapLinearProbing<string, double> stockQuotes;
	HashMapLinearProbing<string, double> stockQuotes(1024); //power of 2
	stockQuotes["AAPL"] =  170.5;
	stockQuotes["IBM"] =  142;
	stockQuotes["BIDU"] =  100;

	HashMapLinearProbing<string, double> stockQuotes2 = stockQuotesz;

	cout << stockQuotes.get("AAPL") << '\n';
	cout << stockQuotes.get("AAPL") << '\n';
}
