#include<iostream>
using namespace std;

template<typename T>
class CircularBuffer {
private:
	int size;
	T* data;
	int head, tail;
	void grow() { //O(n)
		T* old = data;
		data = new T[size + size];
//		data = new char[sizeof(T) * size];
		// first copy from head to end
		int j = 0;
		for(int i = head; i < size; i++, j++){
			data[j] = old[i];
		}
		for(int i = 0; i < size; i++, j++){
			data[j] = old[i];
		}
		head = 0;
		tail = size;
		size = size * 2;
		delete [] old;
	}
public:
	CircularBuffer(int iniSize) : size(iniSize), data(new T[iniSize]), head(0), tail(0) {}
	bool isEmpty() const {
		return tail != head;
	}
	void enqueue(const T& v) {
		data[tail] = v;
		tail = tail + 1;
		if (tail > size) 
			tail = 0;
		if(head == tail) { //just become full
			grow();
		}

	}
	int dequeue() {
		int v = data[head];		
		head = head + 1;
		if( head > size)
			head = 0;
		return v;
	}
};

int main() {
	CircularBuffer<int> c(10);
	for(int i = 0; i < 20; i++)
		c.enqueue(i);
	while(!c.isEmpty())
		cout << c.dequeue();
}
