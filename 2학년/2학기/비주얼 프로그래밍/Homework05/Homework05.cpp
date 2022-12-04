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
	static int x, y;
	static RECT rectView;
	switch (iMsg)
	{
	case WM_CREATE:
		
		x = 20; 
		y = 20;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rectView);
		Rectangle(hdc,rectView.left,rectView.top,rectView.right-40,rectView.bottom-40);
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_KEYDOWN:
		
		if(wParam == VK_RIGHT) { 
			x += 40; 
			if (x + 20 > rectView.right-40)
				x = rectView.right - 60;
		}
		else if (wParam == VK_LEFT) {
			x -= 40;
			if (x - 20 < rectView.left)
				x = rectView.left+20;
		}
		else if (wParam == VK_UP){ 
			y -= 40; 
			if (y - 20 < rectView.top)
				y = rectView.top + 20;
		}
		else if (wParam == VK_DOWN) {
			y += 40;
			if (y + 20 > rectView.bottom - 40)
				y = rectView.bottom - 60;
		}

		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
