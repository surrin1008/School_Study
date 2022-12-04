#include <windows.h>
#include <TCHAR.h>
#include <math.h>
#include "resource.h"
#define BSIZE 40 

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	hInst = hInstance;
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
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static bool selection;
	static HBITMAP hBitmap,hhBitmap;
	static int x, y, my, mx, lx, ly;

	switch (iMsg)
	{
	case WM_CREATE:
		selection = false;
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5_10_2));
		hhBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5_10_1));
		x = 50; y = 50;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (selection) {
			memdc = CreateCompatibleDC(hdc);
			SelectObject(memdc, hBitmap);
			BitBlt(hdc, mx, my, 332, 240, memdc, 0, 0, SRCCOPY);
			DeleteDC(memdc);
		}
		else KillTimer(hwnd, 1);

		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hhBitmap); 
		BitBlt(hdc, x, y, 332, 240, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);

		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		selection = TRUE;
		my = HIWORD(lParam);
		mx = LOWORD(lParam);
		lx = (mx - x) / 8;
		ly = (my - y) / 8;
		SetTimer(hwnd, 1, 70, NULL);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		if (selection) {
			my = HIWORD(lParam);
			mx = LOWORD(lParam);
			lx = (mx - x) / 8;
			ly = (my - y) / 8;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;
	case WM_TIMER:
		if (wParam == 1) {
			if (x > mx - 8 && x < mx + 8)		selection = FALSE;
			else {
				x += lx;
				y += ly;
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_LBUTTONUP:
		selection = FALSE;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}