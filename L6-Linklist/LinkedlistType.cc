class LinkedList1 {
private:
	class Node{
	public:
		int data;
		Node* next;
		Node(int v, Node* next) : data(v), next(next) {}
	};
	Node* head;
	int size_;
public:
	LinkedList1() : head(nullptr) , size_(0){}
	~LinkedList1() {
		for(Node* p = head; p != nullptr; ) {
			Node* q = p;
			p = p->next
			delete q; //wrong, error, if only delete p and just p->next
		}
	}
	LinkedList1(const LinkedList1& orig) {
		if(orig.head == nullptr) { //no element
			head = nullptr;
			return;
		}
		head = new Node(orig.head->data, nullptr);
		if(orig.head->next = nullptr) { //1 element
			return;
		}
		//head is copy of the 1st elemnt of orig
		Node* q = head;
		for(Node* p = orig.head->next; p != nullptr; p = p->next) {
			Node* temp = new Node(p->data, nullptr);
			q->next = temp;
			q = temp;
		}
	}
	LinkedList1& operator =(const LinkedList1& orig) {
		LinkedList1 copy(orig);
		swap(head, copy.head);
		return copy;
	}
	
	void addFirst(int v) { //O(1)
		size_++;
		// head = new Node(v, head);
		Node* temp = new Node();
		temp->data = v;
		temp->next = head;
		head = temp;
	}

	void addEnd(int v) { //O(n)
		size_++;
		Node* p;
		if(head == nullptr) {
			//head = new Node(v, nullptr)
			head = new Node();
			head->data = v;
			head->next = nullptr;
			return;
		}
		for(p = head; p->next != nullptr; p = p->next)
			;
		Node* temp = new Node();
		temp->data = v;
		temp->next = nullptr;
		p->next = temp;
		//p->next = new Node(v, head);
	}

	void removeFirst() { //O(1)
		size_--;
		Node* p = head;
		head = head->next;
		delete p;
	}
	void removeEnd() {
		size_--;
		if(head == nullptr) {
			return;
		}
		Node* p = head;
		if(p->next == nullptr) {
			delete p;
			head = nullptr;
			return;
		}
		Node* q = p->next;
		for(p = head; q->next != nullptr; p = q, q = q->next) //O(n)
			;
		//q points to the last element
		//p points to the last 2nd element
		delete p;
		p->next = nullptr;
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
			int operator *() const {
				return current->data;
			}
	};
};

class LinkedList2 {
private:
	class Node{
	public:
		int data;
		Node* next;

	};
	Node* head;
	Node* tail;
};

class DoubleLinkedList1 {
private:
	class Node{
	public:
		int data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
};

class DoubleLinkedList2 {
private:
	class Node{
	public:
		int data;
		Node* next;
		Node* prev;
		Node(int v, Node* next, Node* prev) : data(v), next(next), prev(prev) {}
	};
	Node* head;
	Node* tail;
public:
	DoubleLinkedList2() {
		head = nullptr;
		tail = nullptr;
	}
	//copy 
	DoubleLinkedList2(const DoubleLinkedList2& orig) {
	
		for(Node p = head->next; p != nullptr; p = p->next) {
			Node* temp = new Node(p.data, nullptr, q);
		}
	}
	void addFirst(int v) {
		
		Node* temp = new Node();
		temp->data = v;
		temp->next = head;
		temp->prev = nullptr;
		if(head == null) {
			tail = temp;
			return;
		} else {
			head->prev = temp;
		}
		head = temp;
	}

	void addEnd(int v) {
		Node* temp = new Node();
		temp->data = v;
		temp->next = nullptr;
		temp->prev = tail;
		if( tail == nullptr) 
			head = temp;
		else
			tail->next = temp;
		tail = temp;
	}

	void removeFirst() {
		if(head == nullptr) 
			return;
		if(tail->prev == nullptr) {
			head = tail = nullptr;
			return;
		}
		head = head->next;
		head->prev = nullptr;
	}

	void removeEnd() {
		if(tail == nullptr)
			return;
		if(tail->prev == nullptr) {
			head = tail = nullptr;
			return;
		}
		tail = tail->prev;
		tail->next = nullptr;
	}
	int size() const {
		int count = 0;
		for(Node* p = head; p != nullptr; p = p->next)	
			count++;
		return count;
	}
	
	class Iterator {
		private:
			Node* current;
		public:
			Iterator(const LinkedList1& list) {
				current = list.head;	
			}
			bool hasNext() {
				return current != nullptr;
			}
			void next() {
				current = current->next;
				return *this;
			}
			int getValue() {
				return current->data;
			}
	};
};

};
//special case head->prev can be used for tail
class DoubleLinkedList3 {
private:
	class Node{
	public:
		int data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
}
