//Xin Song 
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class LinkedList2 {
private:
	class Node{
		public:
			int data;
			Node* next;
			Node(int v, Node* next) : data(v), next(next) {}
	};
	Node* head;
	Node* tail;
	int size;
public:
	LinkedList2() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	void ADD_FRONT(int a, int step, int b) {
//		cout << "add first" << a << step << b << endl;
		tail = nullptr;
		head = nullptr;
		for(int i = a; i <= b; i += step) {
			size++;
			Node* oldhead = head;
			Node* temp = new Node(i, nullptr);
			if(i == a) tail = temp;
			head = temp;
			head->next = oldhead;
		}
	}
	
	void ADD_BACK(int a, int step, int b) {
//		cout << "add back" << a << step << b << endl;
		if(size == 0) { 
			size++;
			Node* temp = new Node(a, nullptr);
			head = temp;
			tail = temp;
			for(int i = a + step; i <= b; i += step) {
				size++;
				Node* temp = new Node(i, nullptr);
				tail->next = temp;
				tail = temp;
			}
		}
		else{
			for(int i = a; i <= b; i += step) {
				size++;
				Node* temp = new Node(i, nullptr);
				tail->next = temp;
				tail = temp;
			}
		}
/*		cout << size << endl;
		cout << "head:" <<  head->data << endl;		
		cout << "tail:" <<  tail->data << endl;		
*/
	}

	void REMOVE_FRONT(int idx) {
//		cout << "rm front" << idx << endl; 
		if(size == 0 || idx > size) 
			return;
		for(int i = 0; i < idx; ++i) {
			size--;
			Node* p = head;
			head = head->next;
			delete p;
		}
	}
	
	void REMOVE_BACK(int idx) {
//		cout << "rm back" << idx << endl; 
		if(size == 0 || idx > size) 
			return;
		Node* p = head;
		if(size == idx) {
			for(int i = 0; i < idx; ++i) {
				size--;
				Node* q = p;
				p = p->next;
				delete q;
			}
			delete p;
			head = tail = nullptr;
		}
		else {
			for(int i = 0; i < size - idx - 1; ++i) {
				p = p->next;
			}
			tail = p;
			p = p->next;
			for(int i = 0; i < idx; ++i) {
				size--;
				Node* q = p;
				p = p->next;
				delete q;
			}
			delete p;
			tail->next = nullptr;
		}
}

	friend ostream& operator<<(ostream& s, const LinkedList2& list) {
		for(Node* p = list.head; p != nullptr; p = p->next) {
			s << p->data << " " ;
		}
		return s;
	}
};

void read(string filename) {
	ifstream ifs(filename);
	LinkedList2 l;
	if(ifs) {
		string buf;
		string opera = "";
		int a = 0, b = 0, step = 1;
		int idex = 1;
		while(getline(ifs, buf)){
			auto i = buf.find(' ');
			opera = buf.substr(0, i);
		//	cout << opera << endl;
			if(opera == "ADD_FRONT") {
				auto p_a = buf.find_first_of("1234567890");
				auto p1 = buf.find_first_of(":");
				auto p2 = buf.find_last_of(":");
				if(!buf.substr(p_a, p1 - p_a).empty())
					a = stoi(buf.substr(p_a, p1 - p_a));
				if(!buf.substr(p1 + 1, p2 - p1 - 1).empty())
					step = stoi(buf.substr(p1 + 1, p2 - p1 - 1));
				if(!buf.substr(p2 + 1).empty())
					b = stoi(buf.substr(p2 + 1));
				l.ADD_FRONT(a, step, b);
			}
			if(opera == "ADD_BACK") {
				auto p_a = buf.find_first_of("1234567890");
				auto p1 = buf.find_first_of(":");
				auto p2 = buf.find_last_of(":");
				if(!buf.substr(p_a, p1 - p_a).empty())
					a = stoi(buf.substr(p_a, p1 - p_a));
				if(!buf.substr(p1 + 1, p2 - p1 - 1).empty())
					step = stoi(buf.substr(p1 + 1, p2 - p1 - 1));
				if(!buf.substr(p2 + 1).empty())
					b = stoi(buf.substr(p2 + 1));
				l.ADD_BACK(a, step, b);
			}
			if(opera == "OUTPUT") {
				cout << l;
				cout << endl;
			}
			if(opera == "REMOVE_FRONT") {
				auto p_idex = buf.find_first_of("1234567890");
				if(p_idex != string::npos)
					idex = stoi(buf.substr(p_idex));
				l.REMOVE_FRONT(idex);
			}
			if(opera == "REMOVE_BACK") {
				auto p_idex = buf.find_first_of("1234567890");
				if(p_idex != string::npos)
					idex = stoi(buf.substr(p_idex));
				l.REMOVE_BACK(idex);
			}
		}
	}
}

int main() {
	read("HW4b.txt");
}
