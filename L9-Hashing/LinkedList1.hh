#pragma once
#include<iostream>
#include<string>
using namespace std;

class LinkedList1 {
private:
	class Node{
	public:
		string data;
		Node* next;
		Node(string v, Node* next) : data(v), next(next) {}
	};
	Node* head;
	int size_;
public:
	LinkedList1() : head(nullptr) , size_(0){}
	~LinkedList1() {
		for(Node* p = head; p != nullptr; ) {
			Node* q = p;
			p = p->next;
			delete q; //wrong, error, if only delete p and just p->next
		}
	}
	LinkedList1(const LinkedList1& orig) {
		if(orig.head == nullptr) { //no element
			head = nullptr;
			return;
		}
		head = new Node(orig.head->data, nullptr);
		if(orig.head->next == nullptr) { //1 element
			return;
		}
		//head is copy of the 1st elemnt of orig
		else {
			Node* q = head;
			for(Node* p = orig.head->next; p != nullptr; p = p->next) {
				Node* temp = new Node(p->data, nullptr);
				q->next = temp;
				q = temp;
			}
		}
	}
	LinkedList1& operator=(const LinkedList1& orig) {
		LinkedList1 copy(orig);
		swap(head, copy.head);
		return *this;
	}
	
	void addFirst(string v) { //O(1)
		size_++;
		Node* old = head;
		head = new Node(v, old);
	}

	void addEnd(string v) { //O(n)
		size_++;
		if(head == nullptr) {
			head = new Node(v, nullptr);
			return;
		}
		Node* p = head;
		for(; p->next != nullptr; p = p->next)
			;
		p->next = new Node(v, nullptr);
	}

	void removeFirst() { //O(1)
		if(head == nullptr)
			return;
		size_--;
		Node* p = head;
		head = head->next;
		delete p;
		return;
	}
	void removeEnd() {
		size_--;
		if(head == nullptr) {
			return;
		}
		if(head->next == nullptr) {
			Node* p = head;
			head = nullptr;
			delete p;
			return;
		}
		else {
			Node* p = head;
			Node* q = p->next;
			for(; q->next != nullptr; p = q, q = q->next) //O(n)
				;
			//q points to the last element
			//p points to the last 2nd element
			delete q;
			p->next = nullptr;
		}
	}
	void remove(int i){
		if(head == nullptr)
			return;
		Node* p = head;
		for(int j = 0; j < i - 2; j++)
			p = p->next;
		Node* q = p->next;
		p->next = q->next;
		q->next = nullptr;
		delete q;
	}

	int size() const {
		int count = 0;
		for(Node* p = head; p != nullptr; p = p->next)	
			count++;
		return count;
	}
	int cachedSize() const {
		return size_;
	}
	friend ostream& operator<<(ostream& s, const LinkedList1& list) {
		for(Node* p = list.head; p != nullptr; p = p->next) {
			s << p->data << " " ;
		}
		return s;
	}
	//walk through every list
	class Iterator {
		private:
			Node* current;
		public:
			Iterator(const LinkedList1& list) {
				current = list.head;	
			}
			bool operator !() const {
				return current != nullptr;
			}
			Iterator& operator ++() {
				current = current->next;
				return *this;
			}
			string operator *() const {
				return current->data;
			}
	};
};
/*
int main() {
	string a = "a";
	string b = "b";
	LinkedList1 l;
	l.addFirst(a);
	cout << l << endl;
	l.addFirst(b);
	cout << l << endl;
	l.addFirst(a);
	cout << l << endl;
	l.addFirst(b);
	cout << l << endl;
	l.remove(3);
	cout << l << endl;
	for(LinkedList1::Iterator i = l; !i; ++i) 
		cout << *i << ' ';
}
*/
