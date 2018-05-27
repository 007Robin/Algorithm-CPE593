#include<iostream>
#include<string>

using namespace std;

template<typename Key, typename Value>
class HashMapLinearProbing {
private:
	class Bucket {
	public:
		Key key;
		Value val;
		bool present;

		Bucket() {
			present = false;
		}
	};
	Bucket* table;
	uint32_t size;
	uint32_t hash(const Key& key) {
		
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
	operator[] (const Key& key) {
		hash(key);
	}
};

int main() {
	HashMapLinearProbing<string, double> stockQuotes;
	stockQuotes["AAPL"] =  170.5;
	stockQuotes["IBM"] =  142;
	stockQuotes["BIDU"] =  100;

	HashMapLinearProbing<string, double> stockQuotes2 = stockQuotesz;

	cout << stockQuotes.get("AAPL") << '\n';
	cout << stockQuotes.get("AAPL") << '\n';
}
