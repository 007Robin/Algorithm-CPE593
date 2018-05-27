#include<iostream>
using namespace std;

class Queue{
private:
	LinkedList2 imp1; //head only, only direction
public:
	void enqueue(int v) {
	//	imp1.addStart(v);	//O(1)
		imp1.addEnd(v);
	}
	int dequeue() { 
		//O(n) return imp1.removeEnd();
		int v = imp1.start();
		imp1.removeStart(); //O(1)
		return v;
	}
	bool isEmpty() const { 
		return imp1.isEmpty();
	}
}
