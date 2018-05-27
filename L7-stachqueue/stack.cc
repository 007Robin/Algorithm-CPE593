#include<iostream>
using namespace std;

class Stack{
private:
	LinkedList1 imp1; //head only, only direction
public:
	void push(int v) {
		imp1.addStart(v);	//O(1)
	}
	int pop() { //O(1)
		int v = imp1.start();
		imp1.removeFirst();
		return v;
	}
	int top() const {
		return imp1.start();  
	}
	bool isEmpty() const { 
		return imp1.isEmpty();
	}
}
