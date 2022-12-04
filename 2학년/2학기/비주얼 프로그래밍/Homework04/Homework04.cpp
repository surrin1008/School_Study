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
	static int mode;
	int i;
	HBRUSH hBrush, oldBrush;
	RECT rect[4] = { {50, 0, 100, 80}, {50, 80, 0, 160},
					{50, 160, 100, 240}, {100, 80, 150, 160} };
	TCHAR direct[4][10] = { _T("위쪽"), _T("왼쪽"), _T("아래쪽"), _T("오른쪽") };

	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < 4; i++)
		{
			Rectangle(hdc, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
			DrawText(hdc, direct[i], _tcslen(direct[i]), &rect[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		switch (wParam)
		{
		case VK_DOWN:
			Rectangle(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
			return 0;
		case VK_UP:
			Rectangle(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
			return 0;
		case VK_LEFT:
			Rectangle(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
			return 0;
		case VK_RIGHT:
			Rectangle(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
			return 0;
		}

	case WM_KEYUP:
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}