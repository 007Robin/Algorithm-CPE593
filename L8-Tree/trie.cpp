//Xin Song -- trie
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
static int cunt = 0;
class Node{
public:
	Node* next[26];
	bool isWord;
	
	Node() {
		for(int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
		isWord = false;
	}

	~Node() {
		for(int i = 0; i < 26; i++) {
			if(next[i] == nullptr) continue;
			delete next[i];
		}
	}
};
class Trie {
private:
	Node* root = nullptr;

public:
	Trie() { // set up the empty trie root contains all null pointers 
		root = new Node();
	}
	
	~Trie() {
		//delete from the leaf
		delete root;
	}
	
	void insert(string word){
		Node* p = root;
		for (int i = 0; i < word.size(); ++i) {
			if (p->next[word[i] - 'a'] == nullptr) {
				p->next[word[i] - 'a'] = new Node();
			}
			p = p->next[word[i] - 'a'];
		}
		p->isWord = true;
	}

	bool contains(string word) {
		Node* p = root;
		for(int i = 0; i < word.size(); ++i) {
			if(p->next[word[i] - 'a'] == nullptr) {
				return false;	
			}
			p = p->next[word[i] - 'a'];
		}
		return p->isWord;
	}

	bool containsPrefix(string word) {
		Node* p = root;
		for(int i = 0; i < word.size(); ++i) {
			if (p->next[word[i] - 'a'] == nullptr) {
				return false;
			}	
			p =  p->next[word[i] - 'a'];
		}
		return true;
	}

};

void load(string filename, Trie& dict) {
	ifstream ifs(filename);
	if(ifs) {
		string s;
		while(ifs >> s) {
			dict.insert(s);
		}
	}
}

int main() {
	Trie dict;
	load("dict.txt", dict);
	ifstream f("hw5.txt");
	if(f) {
		string word; 
		while(f >> word) {
			cout << dict.contains(word) << endl;
		}
	}
//	cout << dict.containsPrefix("ap");
//	cout << dict.containsPrefix("helloni");
}
