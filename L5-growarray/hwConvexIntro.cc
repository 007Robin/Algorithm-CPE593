//Xin Song
#include<iostream>
#include<fstream>
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
//		data = new T[capacity * 2 + 2];
		for(int i = 0; i < capacity; ++i) {
			data[i] = temp[i];
		}
		delete [] temp;
		capacity = 2 * capacity + 2;
	}
public:
	// constructor
	GrowArray() : capacity(0), used(0), data(nullptr) {}
	// allocate memery length first, change char to T type.
	GrowArray(int initialSize) : capacity(initialSize), used(0), data(reinterpret_cast<T*>(new char[sizeof(T) * initialSize])) {}
	// destructor
	~GrowArray() {
		delete [] data;
	}

	// copy constructor
	GrowArray(const GrowArray& orig) : capacity(orig.capacity), used(orig.used), data(reinterpret_cast<T*>(new char[sizeof(T) * orig.capacity])) {
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

	T* getdata() {
		return data;
	}
};


class ConvexHull {
private:
	GrowArray<Point>* grid;
	double minx, miny, maxx, maxy;
	int size;
public:
	ConvexHull() {}
	ConvexHull(int s) : size(s) {
		grid = new GrowArray<Point>[size * size];
		for(int i = 0; i < size * size; ++i) {
			GrowArray<Point> a;
			grid[i] = a;
		}
	}
	~ConvexHull() {
	}
	
	void read(string filename) {
		ifstream ifs(filename);
		GrowArray<Point> points;
		if(ifs) {
			double a, b;
			while(ifs >> a >> b) {
				Point temp = Point(a, b);
				points.addEnd(temp);
			}
		}
		// get minx, maxx, miny, maxy
		minx = points.getdata()[0].x, maxx = points.getdata()[0].x, miny = points.getdata()[0].y, maxy = points.getdata()[0].y;
		for(int i = 0; i < points.size(); ++i) {
			if(points.getdata()[i].x < minx) {
				minx = points.getdata()[i].x;
			}
			if(points.getdata()[i].x > maxx) {
				maxx = points.getdata()[i].x;
			}
			if(points.getdata()[i].y < miny) {
				miny = points.getdata()[i].y;
			}
			if(points.getdata()[i].y > maxy) {
				maxy = points.getdata()[i].y;
			}
		}
		// add point into grid
		double rangex = (maxx - minx) / size;
		double rangey = (maxy - miny) / size;
		for(int i = 0; i < points.size(); i++) {
			int x = (int)((points.getdata()[i].x - minx) / rangex);
			int y = (int)((points.getdata()[i].y - miny) / rangey);
			x = x == size ? size - 1 : x;
			y = y == size ? size - 1 : y;
			grid[x * size + y].addEnd(points.getdata()[i]);
		}

	}

	void printAllListSizes() {
		for(int i = 0; i < size * size; ++i) 
			cout << i << " : " <<  grid[i].size() << endl;
		return; 
	}

	void printMinMax() {
		cout << "minx = "  << minx << "  maxx = " << maxx << "  miny = " << miny << "  maxy = " << maxy << endl;
	}

	void printPerimeterClockWiseOrder() {
		for(int i = 0; i < size; i++) {
			cout << "grid[" << i << "] :";
			for(int j = 0; j < grid[i].size(); ++j) 
				cout << grid[i].getdata()[j] << " ";
			cout << endl;
		}
		for(int i = 2; i <= size; i++) {
			cout << "grid[" << i * size - 1 << "] :";
			for(int j = 0; j < grid[i * size - 1].size(); ++j) 
				cout << grid[i * size - 1].getdata()[j] << " ";
			cout << endl;
		}
		for(int i = size * size - 2, j = 0; j < size - 1; ++j, --i) {
			cout << "grid[" << i << "] :";
			for(int j = 0; j < grid[i].size(); ++j) 
				cout << grid[i].getdata()[j] << " ";
			cout << endl;
		}
		for(int i = size - 2; i > 0; --i) {
			cout << "grid[" << i * size << "] :";
			for(int j = 0; j < grid[i * size].size(); ++j) 
				cout << grid[i * size].getdata()[j] << " ";
			cout << endl;
		}
	}

};

int main() {
	// for homework n=16
	ConvexHull ch(4); // create a 16x16 grid of GrowArray
	ch.read("convexhullpoints.dat");
	ch.printAllListSizes(); // tell us how many are in each list
	ch.printMinMax(); // print minx, maxx, miny, maxy
	ch.printPerimeterClockWiseOrder(); // p1,p2,p3,p4,p8,p12,p16..
	/*
	   example shown n=4
	   -----------------------
	   | p1 | p2  | p3  | p4 |
	   |    |     |     |    |
	   +----+-----+-----+----+
	   | p5 | p6  | p7  | p8 |
	   |    |     |     |    |
	   +----+-----+-----+----+
	   | p9 | p10 | p11 | p12|
	   |    |     |     |    |
	   +----+-----+-----+----+
	   | p13| p14 | p15 | p16|
	   |    |     |     |    |
	   +----+-----+-----+----+
	 */
}
