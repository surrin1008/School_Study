#include <windows.h>
#include <TCHAR.h>
#include "resource.h"
#define LINE 1
#define ELLIPSE 2
#define RECTANGLE 3



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

COLORREF ColorSelection(HWND hwnd, COLORREF oldcolor) {


	COLORREF tmp[16];


	CHOOSECOLOR COLOR;//구조체 변수

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
		return oldcolor;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	HBRUSH hBrush;
	CHOOSECOLOR COLOR;
	static COLORREF temp[16], PenColor = RGB(0, 0, 0), FaceColor = RGB(255, 255, 255);

	static bool Drag = false;
	static int startX, startY, endX, endY;
	static int mode = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PENCOLOR:
			PenColor = ColorSelection(hwnd, PenColor);
			break;
		case ID_FACECOLOR:
			FaceColor = ColorSelection(hwnd, FaceColor);
			break;
		case ID_LINE:
			mode = LINE;
			break;
		case ID_ELLIPSE:
			mode = ELLIPSE;
			break;
		case ID_RECTANGLE:
			mode = RECTANGLE;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		Drag = true;
		startX = LOWORD(lParam);
		startY = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		hdc = GetDC(hwnd);
		Drag = false;
		hPen = CreatePen(PS_SOLID, 1, PenColor);
		SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(FaceColor);
		SelectObject(hdc, hBrush);
		endX = LOWORD(lParam);
		endY = HIWORD(lParam);
		switch (mode)
		{
		case 1:
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY);
			break;
		case 2:
			Ellipse(hdc, startX, startY, endX, endY);
			break;
		case 3:
			Rectangle(hdc, startX, startY, endX, endY);
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
