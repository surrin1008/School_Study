#include <windows.h>
#include <TCHAR.h>
#define LEFT 0
#define TOP 500 
#define RIGHT 300
#define BOTTOM TOP+20

#define LINE 1
#define ELLIPSE 2
#define RECTANGLE 3

int ObjectKind;
int x1, y1, x2, y2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void Parsing(TCHAR str[]);

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
	WndClass.lpszMenuName = NULL;
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
	static TCHAR str[100];
	static int count;
	static SIZE size;

	switch (iMsg)
	{
	case WM_CREATE:
		count = 0;
		str[count] = NULL;
		ObjectKind = 0;
		CreateCaret(hwnd, NULL, 5, 15);
		ShowCaret(hwnd);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, LEFT, TOP, RIGHT, BOTTOM);

		TextOut(hdc, LEFT + 0, TOP, str, _tcslen(str));

		GetTextExtentPoint(hdc, str, count, &size);
		SetCaretPos(LEFT + size.cx, TOP);
		if (ObjectKind == 1)
		{
			MoveToEx(hdc, x1, y1, NULL);
			LineTo(hdc, x2, y2);
		}
		else if (ObjectKind == 2)
			Ellipse(hdc, x1, y1, x2, y2);
		else if (ObjectKind == 3)
			Rectangle(hdc, x1, y1, x2, y2);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			Parsing(str);
			count = 0;
		}
		else if (wParam == VK_BACK) {
			if (count > 0) count--;
		}
		else
			str[count++] = wParam;
		str[count] = NULL;

		InvalidateRgn(hwnd, NULL, TRUE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		HideCaret(hwnd);
		DestroyCaret();
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
void Parsing(TCHAR str[]) {
	TCHAR cmd[20], argNum[20];
	int i = 0, j = 0;
	while (str[i] != '(')
	{
		cmd[j++] = str[i++];
	}
	cmd[j] = NULL;
	j = 0;
	while (str[i] != NULL)
		argNum[j++] = str[i++];
	argNum[j] = NULL;

	_stscanf_s(argNum, _T("(%d, %d, %d, %d)"), &x1, &y1, &x2, &y2);

	if (!_tcscmp(cmd, _T("Line"))) ObjectKind = LINE;
	else if (!_tcscmp(cmd, _T("Ellipse"))) ObjectKind = ELLIPSE;
	else if (!_tcscmp(cmd, _T("Rectangle"))) ObjectKind = RECTANGLE;
}