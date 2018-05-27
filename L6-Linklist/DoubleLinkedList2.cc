#include<iostream>
using namespace std;

class DoubleLinkedList2 {
private:
	class Node{
	public:
		int data;
		Node* next;
		Node* prev;
		Node(Node* prev, int v, Node* next) : prev(prev), data(v), next(next) {}
	};
	Node* head;
	Node* tail;
public:
	DoubleLinkedList2() {
		head = nullptr;
		tail = nullptr;
	}
	~DoubleLinkedList2() {
		for(Node* p = head; p != nullptr; ) {
			Node* q = p;
			p = p->next;
			delete q;
		}	
	}
	//copy 
	DoubleLinkedList2(const DoubleLinkedList2& orig) {
		if(orig.head == nullptr) {
			head = tail = nullptr;
			return;
		}
		head = new Node(nullptr, orig.head->data, nullptr);
		tail = head;
		if(orig.head->next == nullptr)
			return;
		else {
			Node* q = head;
			for(Node* p = orig.head->next; p != nullptr; p = p->next) {
				Node* temp = new Node(q, p->data, nullptr);
				q->next = temp;
				q = q->next;
				tail = temp;
			}
		}
	}

	DoubleLinkedList2& operator =(const DoubleLinkedList2& orig) {
		DoubleLinkedList2 copy(orig);
		swap(head, copy.head);
		swap(tail, copy.tail);
		return *this;
	}

	void addFirst(int v) {
		Node* temp = new Node(nullptr, v, head);
		if(head == nullptr || tail == nullptr) {
			head = tail = temp;
			return;
		} else {
			head->prev = temp;
			head = temp;
		}
	}

	void addEnd(int v) {
		Node* temp = new Node(tail, v, nullptr);
		if (head == nullptr || tail == nullptr) {
			head = tail = temp;
			return;
		} else {
			tail->next = temp;
			tail = temp;
		}
	}

	void removeFirst() {
		if (head == nullptr)
			return;
		if (head == tail) {
			delete head;
			head = tail = nullptr;
			return;
		}
		Node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}

	void removeEnd() {
//		cout << "head:" <<  head->data << endl;
//		cout << "tail:" <<  tail->data << endl; 
		if (tail == nullptr)
			return;
		if (head == tail) {
			delete head;
			head = tail = nullptr;
			return;
		}
		Node* secondToLast = tail->prev;
		delete tail;
		secondToLast->next = nullptr;
		tail = secondToLast;
//		cout << "head:" <<  head->data << endl;
//		cout << "tail:" <<  tail->data << endl; 
	}
	int size() const {
		int count = 0;
		for(Node* p = head; p != nullptr; p = p->next)	
			count++;
		return count;
	}
	
	friend ostream& operator<<(ostream& s, const DoubleLinkedList2& l) {
		for(Node* p = l.head; p != nullptr; p = p->next)
			s << p->data << " ";
		return s;
	}

	class Iterator {
	private:
		Node* current;
	public:
		Iterator(const DoubleLinkedList2& orig) : current(orig.head)  {}
		bool operator !() const { return current != nullptr;  }
		Iterator& operator ++() {
			current = current->next;
			return *this;
		}
		int operator *()const { return current->data; }
	};
};

int main(){
     DoubleLinkedList2 l;
     l.addFirst(1);
     cout << l << endl;
     l.addEnd(2);
     cout << l << endl;
     l.addFirst(0);
     cout << l << endl;
     DoubleLinkedList2 l2(l);
     cout << "l2 = " << l2 << endl;
     l.removeFirst();
     cout << l << endl;
     l.removeEnd();
     cout << l << endl;

}

