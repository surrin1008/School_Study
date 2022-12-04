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
	static BOOL flag = FALSE;
	static int flag_start = -1;
	int i;
	static BOOL flag_right = FALSE;
	static RECT rectView;
	HBRUSH hBrush, oldBrush;
	static RECT rect[5] = { {100,100,200,200} ,{0,100,100,200}, {100,0,200,100} ,{200,100,300,200}, {100,200,200,300} };
	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		if (flag)
		{
			hdc = BeginPaint(hwnd, &ps);
			Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
			DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			if (flag_start % 4 == 0)
			{
				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 1)
			{
				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 2)
			{
				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 3)
			{
				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[4].left, rect[4].top, rect[4].right, rect[4].bottom);
				DrawText(hdc, _T("4"), _tcslen(_T("4")), &rect[4], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
		}

		break;
	
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		switch (wParam)
		{
		case VK_RETURN:
			if (!flag)
			{
				flag = TRUE;
			}
			return 0;

		case VK_SPACE:
			flag_start += 1;
			return 0;
		
		case VK_DOWN:
			if (flag_start % 4 == 0)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 1)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 2)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 3)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			return 0;

		case VK_UP:
			if (flag_start % 4 == 0)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 1)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 2)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 3)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[4].left, rect[4].top, rect[4].right, rect[4].bottom);
				DrawText(hdc, _T("4"), _tcslen(_T("4")), &rect[4], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			return 0;

		case VK_RIGHT:
			GetClientRect(hwnd, &rectView);

			if (flag_start % 4 == 0)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 1)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 2)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 3)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[1].left, rect[1].top, rect[1].right, rect[1].bottom);
				DrawText(hdc, _T("1"), _tcslen(_T("1")), &rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[4].left, rect[4].top, rect[4].right, rect[4].bottom);
				DrawText(hdc, _T("4"), _tcslen(_T("4")), &rect[4], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			if(flag_right)
			for (i = 0; i < 5; i++)
			{
				rect[i].left += 30;
				rect[i].right += 30;
			}
			if (rect[3].right + 30 < rectView.right)
			{
				flag_right = TRUE;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			return 0;

		case VK_LEFT:
			if (flag_start % 4 == 0)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			else if (flag_start % 4 == 1)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 2)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
			else if (flag_start % 4 == 3)
			{
				Ellipse(hdc, rect[0].left, rect[0].top, rect[0].right, rect[0].bottom);
				DrawText(hdc, _T("0"), _tcslen(_T("0")), &rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[2].left, rect[2].top, rect[2].right, rect[2].bottom);
				DrawText(hdc, _T("2"), _tcslen(_T("2")), &rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[3].left, rect[3].top, rect[3].right, rect[3].bottom);
				DrawText(hdc, _T("3"), _tcslen(_T("3")), &rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				Ellipse(hdc, rect[4].left, rect[4].top, rect[4].right, rect[4].bottom);
				DrawText(hdc, _T("4"), _tcslen(_T("4")), &rect[4], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			}
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