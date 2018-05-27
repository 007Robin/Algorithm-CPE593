#include<iostream>
using namespace std;

class DoubleLinkedList3 {
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
	DoubleLinkedList3() {
		head = nullptr;
	}
	DoubleLinkedList3(const DoubleLinkedList3& orig) {
		// 0 element copy
		if(orig.head == nullptr){
			head = head->prev = nullptr;
			return;
		}	
		//copy 1 element first
		head = new Node(nullptr, orig.head->data, nullptr);
		head->prev = head;
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
				q->prev = temp;
			}
		}
	}
	~DoubleLinkedList3() {
		for(Node* p = head; p != nullptr; ) {
			Node* q = p;
			p = p->next;
			delete q;
		}	
	}
	void addFirst(int v) { //O(1)
		if(head == nullptr || head->prev == nullptr) {
			Node* temp = new Node(nullptr, v, nullptr);
			head = temp;
			head->prev = temp;
		}
		else {
			Node* oldhead = head;
			Node* tail = head->prev;
			Node* temp = new Node(nullptr, v, oldhead);
			oldhead->prev = temp;
			head = temp;
			temp->prev = head;
			head->prev = tail;
		}
	}
	void addEnd(int v) { //O(1)
		Node* temp = new Node(head->prev, v, nullptr);
		if(head == nullptr || head->prev == nullptr) {
			head = head->prev = nullptr;
		}
		else {
			head->prev->next = temp;
			head->prev = temp; 
		}
	}
	void removeFirst() { //O(1)
		if(head == nullptr) 
			return;
		if(head == head->prev) {
			Node* p = head;
			head = nullptr;
			head->prev = nullptr;
			delete p;
			return;
		}
		Node* tail = head->prev;	
		Node* p = head;
		head = head->next;
		p->next->prev = head;
		delete p;
		head->prev = tail;
	}

	void removeEnd() { //O(1)
	//	cout << "h : " <<head->data << endl;
	//	cout << "t : " << head->prev->data << endl;
		if(head->prev == nullptr) {
			return; 
		}
		if(head == head->prev) {
			Node* p = head;
			head = nullptr;
			head->prev = nullptr;
			delete p;
			return;
		}
		else {
			Node* p = head->prev;
			Node* secondTolast = p->prev;
			secondTolast->next = nullptr;
			head->prev = secondTolast;
			delete p;
		}
	}
	friend ostream& operator<<(ostream& s, const DoubleLinkedList3& l) {
		for(Node* p = l.head; p != nullptr; p = p->next)
			s << p->data << " ";
		return s;
	}
};

int main(){
	DoubleLinkedList3 l;
	l.addFirst(1);
	cout << l << endl;
	l.addEnd(2);
	cout << l << endl;
	l.addFirst(0);
	cout << l << endl;
	DoubleLinkedList3 l2(l);
	cout << "l2 = " << l2 << endl;
	l.removeFirst();
	cout << l << endl;
	l.removeEnd();
	cout << l << endl;
}
