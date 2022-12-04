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
	hwnd = CreateWindow( _T("Window Class Name"),
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
	while(GetMessage(&msg, NULL, 0, 0))
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
	int x;
	int y;
	TCHAR str[100];
	switch (iMsg) 
	{
	case WM_CREATE:
		break;

	case WM_CHAR:
		x = rand() % 900;
		y = rand() % 700;
		hdc = GetDC(hwnd);
		str[0] = wParam;
		str[1] = NULL;
		TextOut(hdc, x, y, str, _tcslen(str));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}