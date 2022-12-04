#include <iostream>
using namespace std;

class Point {
private:
	int x;
	int y;
public:
	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
	virtual void Draw() {
		cout << "(" << x << ",";
		cout << y << ") ";
	}
};

class Shape {
private:
	Point* p1, * p2;
	string s;

public:
	Shape(int x1, int y1, int x2, int y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
		cout << s;
	}
	virtual void Draw() {

		cout << "좌상단 좌표 : ";
		p1->Draw();
		cout << "우하단 좌표 : ";
		p2->Draw();
		cout << endl;
	}

};

class Circle : public Shape {
private:
	Point* p1, * p2;
public:
	Circle(int x1, int y1, int x2, int y2) :Shape(x1, y1, x2, y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
	}
	void Draw() {
		cout << "원 그린다." << endl;
		cout << "좌상단 좌표 : ";
		p1->Draw();
		cout << "우하단 좌표 : ";
		p2->Draw();
		cout << endl;
	}
};

class Line : public Shape {
private:
	Point* p1, * p2;
public:
	Line(int x1, int y1, int x2, int y2) :Shape(x1, y1, x2, y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
	}
	void Draw() {
		cout << "직선 그린다." << endl;
		cout << "좌상단 좌표 : ";
		p1->Draw();
		cout << "우하단 좌표 : ";
		p2->Draw();
		cout << endl;
	}
};

int main() {
	Circle a(1, 1, 5, 5); // 좌상단점, 우하단점 좌표
	Line b(5, 5, 9, 9); // 좌상단점, 우하단점 좌표
	Shape* p;

	a.Draw(); // “원 그린다” 좌상단/우하단점 좌표 출력
	b.Draw(); // “직선 그린다” 좌상단/우하단점 좌표 출력

	p = new Line(10, 10, 100, 100);
	p->Draw(); // “직선 그린다” 출력, 좌상단/우하단점 좌표 출력
	p = new Circle(100, 100, 200, 200);
	p->Draw(); // “원 그린다” 출력, 좌상단/우하단점 좌표 출력
	delete p;
}