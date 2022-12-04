#include <windows.h>
#include <TCHAR.h>
#include "resource.h"


#define LINE 1
#define CIRCLE 2
#define RECT 3

class Point {
	int x, y;
public:
	Point(int xx = 0, int yy = 0) :x(xx), y(yy)
	{}
	int getX() { return x; }
	int getY() { return y; }
};


class Object {
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
		MoveToEx(hdc, Start.getX(), Start.getY(), NULL);
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




Object* inform[200];

COLORREF ColorSelection(HWND hwnd, COLORREF oldColor) { // 이전 사용하던 color
	COLORREF tmp[16]; CHOOSECOLOR COLOR;
	for (int i = 0; i < 16; i++)
		tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);

	memset(&COLOR, 0, sizeof(CHOOSECOLOR));
	COLOR.lStructSize = sizeof(CHOOSECOLOR);
	COLOR.hwndOwner = hwnd;
	COLOR.lpCustColors = tmp;
	COLOR.Flags = CC_FULLOPEN;
	if (ChooseColor(&COLOR) != 0)
		return COLOR.rgbResult;
	else
		return oldColor;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  	// 커서 지정

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_5);
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static COLORREF color = 0; // 0 이면 검은색
	static COLORREF pencolor = 0;
	HBRUSH hBrush, OldBrush; 
	HPEN oldPEN, hPen;
	static bool Drag;
	static int object[200],oldX[200],oldY[200],startX[200],startY[200];
	static int mx, my;
	static int count = 0;
	switch (iMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_LINE:
			object[count] = LINE;
			break;
		case ID_CIRCLE:
			object[count] = CIRCLE;
			break;
		case ID_RECTANGLE:
			object[count] = RECT;
			break;
		case ID_LINECOLOR:
			pencolor = ColorSelection(hwnd, color);
			break;
		case ID_SHAPECOLOR:
			color = ColorSelection(hwnd, color);
			break;
		}
		break;
	case WM_CREATE:
		Drag = false;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (int i = 0; i < count+1; i++) {
			switch (object[i])
			{
			case LINE:
				inform[i] = new Line_shape(startX[i], startY[i], oldX[i], oldY[i]);
				inform[i]->Draw(hdc);			
				break;
			case CIRCLE:
				inform[i] = new Circle_shape(startX[i], startY[i], oldX[i], oldY[i]);
				inform[i]->Draw(hdc);				
				break;
			case RECT:
				inform[i] = new Rect_shape(startX[i], startY[i], oldX[i], oldY[i]);
				inform[i]->Draw(hdc);			
				break;
			default:
				break;
			}
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		Drag = true;
		startX[count] = LOWORD(lParam);
		startY[count] = HIWORD(lParam);
		oldX[count] = LOWORD(lParam);
		oldY[count] = HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:
		if (Drag) {
			hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);

			switch (object[count]) {
			case LINE:
				SelectObject(hdc, (HPEN)GetStockObject(pencolor));
				mx = LOWORD(lParam);
				my = HIWORD(lParam);

				MoveToEx(hdc, startX[count], startY[count], NULL);
				LineTo(hdc, oldX[count], oldY[count]);
				MoveToEx(hdc, startX[count], startY[count], NULL);
				LineTo(hdc, mx, my);

				oldX[count] = mx; oldY[count] = my;
				break;
			case CIRCLE:
				SelectObject(hdc, (HPEN)GetStockObject(color));
				mx = LOWORD(lParam);
				my = HIWORD(lParam);

				Ellipse(hdc, startX[count], startY[count], oldX[count], oldY[count]);
				Ellipse(hdc, startX[count], startY[count], mx, my);

				oldX[count] = mx; oldY[count] = my;
				break;
			case RECT:
				SelectObject(hdc, (HPEN)GetStockObject(color));
				mx = LOWORD(lParam);
				my = HIWORD(lParam);

				Rectangle(hdc, startX[count], startY[count], oldX[count], oldY[count]);
				Rectangle(hdc, startX[count], startY[count], mx, my);

				oldX[count] = mx; oldY[count] = my;
				break;
			}
			ReleaseDC(hwnd, hdc);
		}
		break;
	case WM_LBUTTONUP:
		if (Drag) {
			object[count + 1] = object[count];
			if (count < 199)count++;
		}
		Drag = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}