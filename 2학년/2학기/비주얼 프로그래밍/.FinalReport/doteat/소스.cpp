#include <windows.h>
#include <TCHAR.H>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	hwnd;
	MSG 	msg;
	WNDCLASS	WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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



#define ITEMNUM 5

int board[22][22];
int wormX[30], wormY[30];
int xDirect, yDirect, len;
static int CountItem, Remaining_Count = 10;
static int Speed = 100;


void ItemGenerator()
{
	int i, x, y;
	for (i = 0; i < ITEMNUM; i++)
	{
		x = rand() % 20 + 1;
		y = rand() % 20 + 1;
		if (board[y][x] == 0)
			board[y][x] = 2;
		else
		{
			i = i - 1;
			continue;
		}
	}
	return;
}

void ItemGenerator_2()
{
	int i, x, y;
	for (i = 0; i < CountItem; i++)
	{
		x = rand() % 20 + 1;
		y = rand() % 20 + 1;
		if (board[y][x] == 0 && !(board[y][x] == 2))
			board[y][x] = 2;
		else
		{
			i = i - 1;
			continue;
		}
	}
	CountItem--;
	return;
}


void DrawGameBoard(HDC hdc,HWND hwnd)
{
	int i, x, y;
	
	if (CountItem == 1 && Remaining_Count != 0)
	{
		ItemGenerator_2();
		Remaining_Count--;
	}
	
	if (Remaining_Count == 0)
	{
		KillTimer(hwnd, 1);
		MessageBox(hwnd,
			_T("게임 클리어!"),
			_T("message"),
			MB_OK);
	}

	for (y = 0; y < 22; y++) {
		for (x = 0; x < 22; x++)
		{
			switch (board[y][x])
			{
			case -1:
				Rectangle(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
				break;
			case 2:
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				Ellipse(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
				SelectObject(hdc, GetStockObject(WHITE_BRUSH));
				break;
			}
		}
	}

	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
	Ellipse(hdc, wormX[0] * 20, wormY[0] * 20, (wormX[0] + 1) * 20, (wormY[0] + 1) * 20);
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));

	for (i = 1; i < len; i++)
		Ellipse(hdc, wormX[i] * 20, wormY[i] * 20, (wormX[i] + 1) * 20, (wormY[i] + 1) * 20);
}


void GameInit()
{
	int i;
	int j;

	for (i = 0; i < 22; i++)
	{
		board[i][0] = -1;
		board[i][21] = -1;
		board[0][i] = -1;
		board[21][i] = -1;
	}
	wormX[0] = 2; wormY[0] = 1;
	wormX[1] = 1; wormY[1] = 1;
	board[wormY[0]][wormX[0]] = 3;
	board[wormY[1]][wormX[1]] = 3;

	ItemGenerator();

	len = 2;
	xDirect = 1; yDirect = 0;
}

void BoardReset()
{
	int i, j;
	for (i = 0; i < 22; i++)
		for (j = 0; j < 22; j++)
		{
			board[j][i] = 0;
		}
}

void DirectControl(int DirectKey)
{
	switch (DirectKey) {
	case VK_LEFT:
		if (xDirect == 1)
			break;
		if (board[wormY[0]][wormX[0] - 1] != -1)
		{
			xDirect = -1;
			yDirect = 0;
		}
		break;
	case VK_RIGHT:
		if (xDirect == -1)
			break;
		if (board[wormY[0]][wormX[0] + 1] != -1)
		{
			xDirect = 1;
			yDirect = 0;
		}
		break;
	case VK_UP:
		if (yDirect == 1)
			break;
		if (board[wormY[0] - 1][wormX[0]] != -1)
		{
			xDirect = 0;
			yDirect = -1;
		}
		break;
	case VK_DOWN:
		if (yDirect == -1)
			break;
		if (board[wormY[0] + 1][wormX[0]] != -1)
		{
			xDirect = 0;
			yDirect = 1;
		}
		break;
	}
}


void MovingWorm(HWND hwnd)
{
	int tmpx, tmpy, i;

	tmpx = wormX[0];
	tmpy = wormY[0];
	wormX[0] += xDirect; wormY[0] += yDirect;

	if (board[wormY[0]][wormX[0]] == -1 || board[wormY[0]][wormX[0]] == 3)
	{
		wormX[0] = tmpx;
		wormY[0] = tmpy;
		KillTimer(hwnd, 1);
		MessageBox(hwnd,
			_T("게임 탈락!"),
			_T("message"),
			MB_OK);
	}
	else
	{
		if (board[wormY[0]][wormX[0]] == 2)
		{
			len = len + 1;
			board[wormY[0]][wormX[0]] = 0;
			CountItem++;
		}
		else
			board[wormY[len - 1]][wormX[len - 1]] = 0;

		for (i = len - 1; i > 1; i--)
		{
			wormX[i] = wormX[i - 1];
			wormY[i] = wormY[i - 1];
		}
		wormX[1] = tmpx;
		wormY[1] = tmpy;
		board[wormY[0]][wormX[0]] = 3;
	}
}

void MenuEvent(WPARAM wParam,HWND hwnd)
{
	switch (wParam)
	{
	case ID_PAUSE:
		KillTimer(hwnd, 1);
		break;
	case ID_START:
		SetTimer(hwnd, 1, Speed, NULL);
		break;
	case ID_RESTART:
		Remaining_Count = 10;
		SetTimer(hwnd, 1, Speed, NULL);
		BoardReset();
		GameInit();
		break;
	case ID_SPEED_SLOW:
		Speed = 150;
		SetTimer(hwnd, 1, Speed, NULL);
		break;
	case ID_SPEED_NOMAL:
		Speed = 100;
		SetTimer(hwnd, 1, Speed, NULL);
		break;
	case ID_SPEED_FAST:
		Speed = 50;
		SetTimer(hwnd, 1, Speed, NULL);
		break;
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hMenu;
	srand(time(NULL));

	switch (iMsg) {
	case WM_CREATE:
		GameInit();
		SetTimer(hwnd, 1, Speed, NULL);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		DrawGameBoard(hdc,hwnd);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		DirectControl((int)wParam);
		break;
	case WM_COMMAND:
		MenuEvent(wParam,hwnd);
		break;
	case WM_TIMER:
		MovingWorm(hwnd);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//갯수 줄어들때 마다 하나씩 추가
//
//메뉴바
//	일시정지 
//	시작
//	다시 시작
//	
//	속도 관리
//
//탈락기능
//
//