#pragma once
#include<iostream>
using namespace std;

template<typename T>
class GrowArray{
public:
//private:
	T* data;
	int capacity;
	int used;
	void grow() {
		if(used < capacity)
			return;
		T* temp = data;
		data = new T[capacity * 2 + 2];
		for(int i = 0; i < used; ++i) {
			data[i] = temp[i];
		}
		if(temp != nullptr) delete [] temp;
		capacity = 2 * capacity + 2;
	}
public:
	// constructor
	GrowArray() : capacity(0), used(0), data(nullptr) {}
	GrowArray(int initialSize) : capacity(initialSize), used(0), data(new T[initialSize]) {}
	// destructor
	~GrowArray() {
		delete [] data;
	}
	
	// copy constructor
	GrowArray(const GrowArray& orig) : capacity(orig.capacity), used(orig.used), data(new T[orig.capacity]) {
		for(int i = 0; i < orig.used; ++i)
			data[i] = orig.data[i];
	}
	// operator = 
	GrowArray& operator =(const GrowArray& orig) {
		GrowArray copy(orig);
		return *copy;
	}

	friend ostream& operator <<(ostream& s, const GrowArray &v) {
		for(int i = 0; i < v.used; ++i) {
			s << v.data[i] << ' ';
		}
		return s;
	}

	
	void addEnd(T v) { //O(1)
		if(used >= capacity)
			grow();
		data[used++] = v;
	}
	void addStart(T v) { //O(n)
		if(used >= capacity)
			grow();
		
		const T* old = data;
		data = new T[used + 1];
		data[0] = v;
		for(int i = 0; i < used; ++i) {
			data[i + 1] = old[i];
		}
		used++;
		delete [] old;
	}
	void insert(int i, T v) {
		if(used >= capacity)
			grow();
				
		const T* old = data;
		data = new T[used + 1];
		for(int j = 0; j < i; j++) {
			data[j] = old[j];
		}
		data[i] = v;
		used++;
		for(int j = i + 1; j < used; ++j) {
			data[j] = old[j - 1];
		}
		delete [] old;
	}
	void removeEnd() {
		used--;	
	}
	void removeStart() {
		for(int i = 0; i < used; i++)
			data[i] = data[i + 1];
		used--;
	}
	void remove(int i) {
		for(int j = i; j < used; j++) {
			data[j] = data[j + 1];
		}
		used--;
	}
	// return how many elements in the list
	int size() const {
		return used;	
	}
};

/*
int main() {
	GrowArray<int> a(10);
	cout << a << endl;
	for(int i = 0; i < 10; i++) {
		a.addEnd(i);
	}
	cout << a << endl;
	cout << a.size() << endl;
    GrowArray<int> b = a;
	cout << b << '\n';
//	GrowArray<int> c(a);
//	cout << c << '\n';
//	b = c; //operator =
//	cout << b << '\n';
}
*/
