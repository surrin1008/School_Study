#pragma once
class Point {
	int x, y;
public:
	Point(int xx = 0, int yy = 0):x(xx), y(yy)
	{}
	int getX() { return x; }
	int getY() { return y; }
};


class Object{
protected:
	Point Start, End;
public:
	Object() {
		Start = Point(0, 0);
		End = Point(0, 0);
	}
	virtual void Draw(HDC hdc) {
		Ellipse(hdc, Start.getX(), Start.getY(), End.getX(), End.getY());
	}
};

class Circle_shape : public Object {
public:
	Circle_shape(int lx, int ly, int rx, int ry) {
		Start = Point(lx, ly);
		End = Point(rx, ry);
	}
	void Draw(HDC hdc) {
		Ellipse(hdc, Start.getX(), Start.getY(), End.getX(), End.getY());
	}
};

class Line_shape : public Object {
public:
	Line_shape(int lx, int ly, int rx, int ry) {
		Start = Point(lx, ly);
		End = Point(rx, ry);
	}
	void Draw(HDC hdc) {
		MoveToEx(hdc, Start.getX(), Start.getY(),NULL);
		LineTo(hdc, End.getX(), End.getY());
	}
};

class Rect_shape : public Object {
public:
	Rect_shape(int lx, int ly, int rx, int ry) {
		Start = Point(lx, ly);
		End = Point(rx, ry);
	}
	void Draw(HDC hdc) {
		Rectangle(hdc, Start.getX(), Start.getY(), End.getX(), End.getY());
	}
};


