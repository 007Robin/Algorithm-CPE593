#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class PerfectHash{
private:
	class HashTable{
	public:
		string* vals = nullptr;
		int size = 0;

		HashTable(int s = 0) : size(s), vals(new string[s]) {
			for(int i = 0; i < size; i++)
				vals[i] = "";
		}

	};
	HashTable* table;
	int size;
	int hash(const string& key, int n) {
		int sum = key.size();
		for(int i = 0; i < key.size(); ++i)
			sum  = (sum << 5) + (sum >> 17) + key[i];
		return sum % n;
	}
public:
	PerfectHash(int intsize = 1024) : size(intsize) {
		table = new HashTable(size);
		creatHashing();
	}
	~PerfectHash() {
		delete [] table;
	}

	void creatHashing(){
		ifstream ifs("dict.txt");
		if(ifs) {
			string s;
			while(ifs >> s) {
				add(s);
			}
		}
	}
	
	void add(const string& key) {
		int pos = hash(key, size);
	/*	int cur_size = table[pos].size;

		if(cur_size != 1) {
			int offset = hash(key, cur_size);
			//after rehash and has space to insert
			if(table.pos.vals[offset] == "") {
				table.pos.vals[offset] = key;
			}
			else{
				//rehash
		while(table[pos].vals[hash(key, table[pos].size)] != "") {
				string* temp = new string[table[];
				for(int i = 0; i < cur_size; ++i)
					temp[i] = table[pos].vals[i];
				delete [] table[pos].vals;

				table[pos].vals = new string[cur_size+1];
				for(int i = 0; i < temp->size(); ++i) {
					if(!temp[i].empty()) {
						int newkey = hash(temp[i], table[pos].size);
						if(table[pos].vals[newkey] == "") {
							table[pos].vals[newkey] = temp[i];
						}
						else {
							table[pos].vals = new string[table[pos].size+1];
							i = 0;
						}
					}
				}
			}
			table[pos].vals[hash(key, table[pos].size)] = key;	
			
		}
		else {
			//normal insert
			if(table[pos].vals->empty()) {
				table[pos].vals[0] = key;
			}
			else {
			//rehash
			while(table[pos].vals[hash(key, table[pos].size)] != "") {
				string* temp = new string[cur_size];
				for(int i = 0; i < cur_size; ++i)
					temp[i] = table[pos].vals[i];
				delete [] table[pos].vals;

				table[pos].vals = new string[cur_size+1];
				for(int i = 0; i < temp->size(); ++i) {
					if(!temp[i].empty()) {
						int newkey = hash(temp[i], table[pos].size);
						if(table[pos].vals[newkey] == "") {
							table[pos].vals[newkey] = temp[i];
						}
						else {
							table[pos].vals = new string[table[pos].size + 1];
							i = 0;
						}
					}
				}
			}
			}

			table[pos].vals[hash(key, table[pos].size)] = key;	
		}
*/
		//insert 1st element
		if(table[pos].size == 0){
			// insert new ele
			table[pos].vals = new string[1];
			table[pos].vals[0] = key;
			table[pos].size = 1;
		}
		//insert >1 element
		else {
			string* store = new string[table[pos].size];
			for(int i = 0; i < table[pos].size; ++i) {
				store[i] = table[pos].vals[i];

			}
			//if collision
			do {
				//rehash
				delete[] table[pos].vals;
				table[pos].vals = new string[table[pos].size + 1];
				for(int i = 0; i < store->size(); i++) {
					if(!store[i].empty()) {
						int key2 = hash(store[i], table[pos].size);
						if(table[pos].vals[key2] != ""){
							delete[] table[pos].vals;
							table[pos].vals = new string[table[pos].size + 1];
							i = 0;
						}
						else {
							table[pos].vals[key2] = store[i];
							table[pos].size++;
						}
					}
				}
			}while(table[pos].vals[hash(key, table[pos].size)] != "");
			
			//if no collision (val == "") then insert key
			table[pos].vals[hash(key, table[pos].size)] = key;
			table[pos].size++;

			delete [] store;

		}
	}

	bool contain(const string s) {
		int pos = hash(s, size);
		if(table[pos].size == 1) {
			if(table[pos].vals->empty()) 
				return false;
			else {
				if(table[pos].vals[0] == s)
					return true;
				return false;
			}
		}
		else {
		
			int key2 = hash(s, table[pos].size);
			if(table[pos].vals[key2].size() == 0)
				return false;
			else if(table[pos].vals[key2] == s) 
				return true;
			return false;
		}
	}
};

int main() {
	PerfectHash m(10);
	cout << m.contain("a");
	cout << m.contain("apple");
	cout << m.contain("wadsa");
}
