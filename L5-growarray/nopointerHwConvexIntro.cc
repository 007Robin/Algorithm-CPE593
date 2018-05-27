#include<iostream>
#include "hwGrowArray.hh"
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
//		delete[] grid;
	}
	
	void read(string filename) {
		ifstream ifs(filename);
		//GrowArray<Point*> points(size * size);
		GrowArray<Point> points;
		if(ifs) {
			double a, b;
			while(ifs >> a >> b) {
				Point temp(a, b);
				points.addEnd(temp);
			}
		}
		minx = points.data[0].x, maxx = points.data[0].x, miny = points.data[0].y, maxy = points.data[0].y;
		for(int i = 0; i < points.size(); ++i) {
			if(points.data[i].x < minx) {
				minx = points.data[i].x;
			}
			if(points.data[i].x > maxx) {
				maxx = points.data[i].x;
			}
			if(points.data[i].y < miny) {
				miny = points.data[i].y;
			}
			if(points.data[i].y > maxy) {
				maxy = points.data[i].y;
			}
		}
		double rangex = (maxx - minx) / size;
		double rangey = (maxy - miny) / size;
		for(int i = 0; i < points.size(); i++) {
			int x = (int)((points.data[i].x - minx) / rangex);
			int y = (int)((points.data[i].y - miny) / rangey);
			x = x == size ? size - 1 : x;
			y = y == size ? size - 1 : y;
//			cout << points.data[i].x << " " << points.data[i].y << endl;
//			cout << x << " " << y << endl;
			grid[x * size + y].addEnd(points.data[i]);
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
		cout << grid[0].data[0] << endl;
		for(int i = 0; i < size; i++) {
			//cout << grid[i] << endl;
			cout << (grid[i]) << endl;
		}
		for(int i = 2; i <= size; i++) {
			cout << grid[i * size - 1] << endl;
			//cout << *grid[i * size - 1] << endl;
		}
		for(int i = size * size - 2, j = 0; j < size - 1; ++j, --i) {
			cout << grid[i] << endl;
			//cout << *grid[i] << endl;
		}
		for(int i = size - 2; i > 0; --i) {
			cout << grid[i * size].data << endl;
			//cout << *grid[i * size].data << endl;
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
