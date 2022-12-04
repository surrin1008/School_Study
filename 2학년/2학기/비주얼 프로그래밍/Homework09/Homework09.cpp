#include <windows.h>
#include <TCHAR.h>

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
	static POINT mouse, cat, MB;
	static BOOL Flag;
	switch (iMsg)
	{
	case WM_CREATE:
		cat.x = cat.y = 100;
		Flag = FALSE;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (Flag)
		{
			TextOut(hdc, mouse.x, mouse.y, _T("쥐"), _tcslen(_T("쥐")));
		}
		TextOut(hdc, cat.x, cat.y, _T("고양이"), _tcslen(_T("고양이")));
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		Flag = TRUE;
		InvalidateRgn(hwnd, NULL, TRUE);
		SetTimer(hwnd, 1, 0.7, NULL);
		break;
	case WM_TIMER:
		if (Flag)
		{
			if (mouse.x - cat.x >= 0)
			{
				cat.x++;
				if (mouse.x == cat.x)
					break;
			}
			else
			{
				cat.x--;
			}
			if (mouse.y - cat.y >= 0)
			{
				cat.y++;
				if (mouse.y == cat.y)
					break;
			}
			else
			{
				cat.y--;
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		Flag = FALSE;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		MB.x = LOWORD(lParam);
		MB.y = HIWORD(lParam);
		if (Flag)
		{
			mouse.x = MB.x;
			mouse.y = MB.y;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}