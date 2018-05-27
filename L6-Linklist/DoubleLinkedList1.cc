#include<iostream>
using namespace std;

class DoubleLinkedList1 {
private:
	class Node{
	public:
		int data;
		Node* next;
		Node* prev;
		Node(Node* prev, int v, Node* next) : prev(prev), data(v), next(next) {}
	};
	Node* head;
public:
	DoubleLinkedList1() {
		head = nullptr;
	}
	DoubleLinkedList1(const DoubleLinkedList1& orig) {
		// 0 element copy
		if(orig.head == nullptr){
			head = nullptr;
			return;
		}	
		//copy 1 element first
		head = new Node(nullptr, orig.head->data, nullptr);
		//if only 1 element
		if(orig.head->next == nullptr) {
			return;
		}
		else {
		//>1 element, copy from 2nd element 
			Node* q = head;
			for(Node* p = orig.head->next; p != nullptr; p = p->next) {
				Node* temp = new Node(q, p->data, nullptr);
				q->next = temp;
				q = temp;
			}
		}
	}
	~DoubleLinkedList1() {
		for(Node* p = head; p != nullptr; ) {
			Node* q = p;
			p = p->next;
			delete q;
		}	
	}
	void addFirst(int v) { //O(1)
		Node* oldhead = head;
		Node* temp = new Node(nullptr, v, oldhead);
		head = temp;
		head->prev = nullptr;

	}
	void addEnd(int v) { //O(n)
		if(head == nullptr) {
			Node* temp = new Node(nullptr, v, nullptr);
			head = temp;
			return;
		}	
		Node* p = head;
		for(; p->next != nullptr; p = p->next) 
			;
		Node* temp = new Node(p, v, nullptr);
		p->next = temp;
	}
	void removeFirst() { //O(1)
		if(head == nullptr) 
			return;
		if(head->next == nullptr) {
			Node* p = head;
			head = nullptr;
			delete p;
			return;
		}
		else {
			Node* p = head;
			head = head->next;
			head->prev = nullptr;
			delete p;
		}
	}

	void removeEnd() { //O(n)
		if(head == nullptr) 
			return; 
		if(head->next == nullptr) {
			Node* p = head;
			head = nullptr;
			delete p;
			return;
		}
		else {
			Node* p = head;
			for(; p->next->next != nullptr; p = p->next) 
				;
			Node* q = p->next;
			p->next = nullptr;
			delete q;
		}
	}
	friend ostream& operator<<(ostream& s, const DoubleLinkedList1& l) {
		for(Node* p = l.head; p != nullptr; p = p->next)
			s << p->data << " ";
		return s;
	}
};

int main(){
	DoubleLinkedList1 l;
	l.addFirst(1);
	cout << l << endl;
	l.addEnd(2);
	cout << l << endl;
	l.addFirst(0);
	cout << l << endl;
	DoubleLinkedList1 l2(l);
	cout << "l2 = " << l2 << endl;
	l.removeFirst();
	cout << l << endl;
	l.removeEnd();
	cout << l << endl;
}
