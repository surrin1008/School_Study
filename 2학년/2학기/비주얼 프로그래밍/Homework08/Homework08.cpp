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
	HPEN hPen, oldPen;
	PAINTSTRUCT ps;
	static int x, y;
	static RECT rectView;
	static bool flag;
	static int count;
	switch (iMsg)
	{
	case WM_CREATE:
		flag = true;
		x = 20;
		y = 20;
		count = 1;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rectView);
		Rectangle(hdc, rectView.left, rectView.top, rectView.right - 40, rectView.bottom - 40);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		SelectObject(hdc, oldPen);
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		switch (count)
		{	
		case 1:
			
			Ellipse(hdc, x - 60, y - 20, x - 20, y + 20);
			break;
		case 2:
			
			Ellipse(hdc, x + 20, y - 20, x + 60, y + 20);
			break;
		case 3:
			
			Ellipse(hdc, x - 20, y + 20, x + 20, y + 60);
			break;
		case 4:
			
			Ellipse(hdc, x - 20, y - 60, x + 20, y - 20);
			break;
		}
		DeleteObject(hPen);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:

		if (wParam == VK_RETURN)
		{
			if (!flag)
			{
				flag = true;
				KillTimer(hwnd, 1);
			}
			else
			{
				SetTimer(hwnd, 1, 70, NULL);
				flag = false;
			}

		}
		else if (wParam == VK_RIGHT)
		{
			count = 1;
		}
		else if (wParam == VK_LEFT)
		{
			count = 2;
		}
		else if (wParam == VK_UP)
		{
			count = 3;
		}
		else if (wParam == VK_DOWN)
		{
			count = 4;
		}

	case WM_TIMER:
		switch (count)
		{
		case 1:
			x += 40;
			if (x + 20 > rectView.right - 40)
				x = rectView.right - 60;
			break;
		case 2:
			x -= 40;
			if (x - 20 < rectView.left)
				x = rectView.left + 20;
			break;
		case 3:
			y -= 40;
			if (y - 20 < rectView.top)
				y = rectView.top + 20;
			break;
		case 4:
			y += 40;
			if (y + 20 > rectView.bottom - 40)
				y = rectView.bottom - 60;
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}