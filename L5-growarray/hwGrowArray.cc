#include<iostream>
using namespace std;

class Point {
	public:
		double x,y;
		Point(double x, double y) : x(x), y(y) {}
		Point(const Point& orig) : x(orig.x), y(orig.y) {}
		friend ostream& operator<<(ostream& s, const Point& p) {
		    return s << "(" << p.x << " , " << p.y << ")" << " ";
		}
};

template<typename T>
class GrowArray{
private:
	T* data;
	int capacity;
	int used;
	void grow() {
		if(used < capacity)
			return;
		T* temp = data;
		data = reinterpret_cast<T*>(new char[sizeof(T) * (capacity * 2 + 2)]);
		//data = new T[capacity * 2 + 2];
		for(int i = 0; i < capacity; ++i) {
			data[i] = temp[i];
		}
		delete [] temp;
		capacity = 2 * capacity + 2;
	}
public:
	// constructor
	GrowArray() : capacity(0), used(0), data(nullptr) {}
//	GrowArray(int initialSize) : capacity(initialSize), used(0), data(new T[initialSize]) {}
	// allocate memery length first, change char to T type.
	GrowArray(int initialSize) : capacity(initialSize), used(0), data(reinterpret_cast<T*>(new char[sizeof(T) * initialSize])) {}
	// destructor
	~GrowArray() {
		delete [] data;
	}
	

	// copy constructor
	GrowArray(const GrowArray& orig) : capacity(orig.capacity), used(orig.used), data(reinterpret_cast<T*>(new char[sizeof(T) * orig.capacity])) {
	//GrowArray(const GrowArray& orig) : capacity(orig.capacity), used(orig.used), data(new T[orig.capacity]) {
		for(int i = 0; i < orig.used; ++i)
			data[i] = orig.data[i];
	 }
	// operator = 
	GrowArray& operator =(const GrowArray& orig) {
		GrowArray copy(orig);
		swap(copy.data, data);
		swap(copy.used, used);
		swap(copy.capacity, capacity);
		return *this;
	}
/*
	*/

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
		for(int j = i; j < used; ++j) {
			data[j + 1] = old[j];
		}
		used++;
		delete [] old;
	}
	void removeEnd() {
		used--;	
	}
	void removeStart() {
		for(int i = 1; i < used; i++)
			data[i - 1] = data[i];
		used--;
	}
	void remove(int i) {
		for(int j = i + 1; j < used; j++) {
			data[j - 1] = data[j];
		}
		used--;
	}
	// return how many elements in the list
	int size() const {
		return used;	
	}

	int removeEnd2() {
		int last = data[used - 1];
		used--;
		return last;
	}

	void removeElements() {
		int k = 0; 
		int* old = data;
		data = new int[used/2];
		for(int i = 0; i < used; i++) {
			if(i % 2 == 0)
				data[k++] = old[i];
		}
		used = used/2;
	}
};

int main() {
	GrowArray<int> a(10);
	for(int i = 0; i < 10; i++) {
		a.addEnd(i + 1);
	}
	cout << a << endl;
	a.removeElements();
	cout <<  " a len is " << a.used << endl;
	cout << a << endl;
/*
	GrowArray<Point> a(10);
	cout << a << endl;
	for(int i = 0; i < 10; i++) {
		Point temp = Point(i, i);
		cout << "temp: " << temp << endl;
		a.addEnd(temp);
	}
	cout << a << endl;
	cout << a.size() << endl;

    GrowArray<Point> b = a;
	cout << "a: " << a << endl;
	cout << b << '\n';
	GrowArray<Point> c(a);
	cout << c << '\n';
//	b = c; //operator =
//	cout << b << '\n';
*/
}
