#include<iostream>
#include "hwGrowArray.hh"
#include<fstream>
using namespace std;

class Point {
	public:
		double x,y;
		Point(double x, double y) : x(x), y(y) {}
		friend ostream& operator<<(ostream& s, const Point& p) {
		    return s << "(" << p.x << " , " << p.y << ")" << " ";
		}
};

class ConvexHull {
private:
	GrowArray<Point*> points;
	int size;
public:
	ConvexHull() {}
	ConvexHull(int size) : size(size), points(size * size) {}
	~ConvexHull() {
		for(int i = 0; i < points.size(); ++i) {
			delete points.data[i];
		}
	}
	
	void read(string filename) {
		ifstream ifs(filename);
		int c = 0;
		if(ifs) {
			double a, b;
			while(ifs >> a >> b) {
				c++;
				cout << a << ", " << b << endl;
				points.addEnd(new Point(a, b));
			}
		}
		cout << "*****"<< c << endl;
		for(int i = 0; i < points.size(); i++) {
			cout << points.data[i]->x << "__" << points.data[i]->y << endl;
		}
		for(int i = points.used; i < points.capacity; ++i)
			points.addEnd(new Point(0, 0));
	
		return;
		double minx = points.data[0]->x, maxx = points.data[0]->x, miny = points.data[0]->y, maxy = points.data[0]->y;
		for(int i = 0; i < points.size(); ++i) {
			if(points.data[i]->x < minx) {
				minx = points.data[i]->x;
			}
			if(points.data[i]->x > maxx) {
				maxx = points.data[i]->x;
			}
			if(points.data[i]->y < miny) {
				miny = points.data[i]->y;
			}
			if(points.data[i]->y > maxy) {
				maxy = points.data[i]->y;
			}
		}
	}

	int printAllListSizes() {
		cout << points.used << endl;
		return points.used;
	}

	void printMinMax() {
	//	cout << "minx = "  << minx << "  maxx = " << maxx << "  miny = " << miny << "  maxy = " << maxy << endl;
	}

	void printPerimeterClockWiseOrder() {
		for(int i = 0; i < size; i++) {
			cout << *points.data[i] << endl;
		}
		for(int i = 2; i <= size; i++) {
			cout << *points.data[i * size - 1] << endl;
		}
		for(int i = size * size - 2, j = 0; j < size - 1; ++j, --i) {
			cout << *points.data[i] << endl;
		}
		for(int i = size - 2; i > 0; --i) {
			cout << *points.data[i * size] << endl;
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
