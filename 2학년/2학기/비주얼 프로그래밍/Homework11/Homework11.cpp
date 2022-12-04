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

#define radius 80
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN redPen, bluePen;
	static int circleX[4][8], circleY[4][8], circle_color[4][8], circlecount;
	static POINT m_point;
	int i, j;

	switch (iMsg)
	{
	case WM_CREATE:
		circlecount = 0;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 8; j++)
			{
				circleX[i][j] = -100;
				circleY[i][j] = -100;
				circle_color[i][j] = 0;
			}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < 9; i++)
		{
			MoveToEx(hdc, i * radius, 0, NULL);
			LineTo(hdc, i * radius, 4*radius);
		}
		for (i = 0; i < 5; i++)
		{
			MoveToEx(hdc, 0, i * radius, NULL);
			LineTo(hdc, 8*radius, i * radius);
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		m_point.x = LOWORD(lParam);
		m_point.y = HIWORD(lParam);
		int x, y;
		x = m_point.x / radius;
		y = m_point.y / radius;
		if (y < 4 && x < 8)
		{
			circleX[y][x] = (x)*radius;
			circleY[y][x] = (y)*radius;
			if (circlecount % 2 == 1)
			{
				if (circle_color[y][x] == 0)
				{
					circle_color[y][x] = 1;
				}
			}
			else
			{
				if (circle_color[y][x] == 0)
				{
					circle_color[y][x] = 2;
				}
			}
			
			redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

			for (i = 0; i < 4; i++)
				for (j = 0; j < 8; j++)
				{
					if (circle_color[i][j] == 1)
					{
						SelectObject(hdc, redPen);
					}
					else if (circle_color[i][j] == 2)
					{
						SelectObject(hdc, bluePen);
					}
					Ellipse(hdc, circleX[i][j], circleY[i][j], circleX[i][j] + radius, circleY[i][j] + radius);
				}
		}
		ReleaseDC(hwnd, hdc);
		break;

	case WM_LBUTTONUP:
		circlecount++;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}