#include <windows.h>
#include <TCHAR.h>
#include <math.h>
#define BSIZE 40
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND     hwnd;
    MSG       msg;
    WNDCLASS WndClass;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);     // 커서 지정

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


float LengthPts(int x1, int y1, int x2, int y2) {
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

BOOL InCircle(int x, int y, int mx, int my) {
    if (LengthPts(x, y, mx, my) < BSIZE)
        return TRUE;
    else
        return FALSE;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static BOOL Selection;
    PAINTSTRUCT ps;
    static int startX, startY, oldX, oldY;
    static BOOL Drag;
    static int endX, endY;
    int mx, my;
    static int lastmoveX, lastmoveY;
    static int x = 0, y = 0;
    HPEN hPen, oldPen;
    HBRUSH hBrush, oldBrush;
    static int move;

    static int stepX = 0, stepY = 0;//이동을 위한 변수 


    switch (iMsg) {

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        if (Selection)
        {
            hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            oldPen = (HPEN)SelectObject(hdc, hPen);

            hBrush = CreateSolidBrush(RGB(0, 255, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);


        }

        Ellipse(hdc, x, y, x + BSIZE, y + BSIZE);//원 출력


        EndPaint(hwnd, &ps);
        break;

    case WM_CREATE:
        startX = oldX = 20;
        startY = oldY = 20;
        Drag = FALSE;
        move = 0;
        stepX = 0;
        stepY = 0;
        break;

    case WM_LBUTTONDOWN:
        mx = LOWORD(lParam);
        my = HIWORD(lParam);

        if (InCircle(x, y, mx, my)) {
            Selection = TRUE;
            startX = LOWORD(lParam);
            startY = HIWORD(lParam);

        }
        Drag = TRUE;
        InvalidateRgn(hwnd, NULL, TRUE);
        break;

    case WM_LBUTTONUP:

        if ((Drag) && (Selection)) {

            stepX = (oldX - startX) / 10;
            stepY = (oldY - startY) / 10;

            SetTimer(hwnd, 1, 10, NULL);
        }

        Drag = FALSE;
        Selection = FALSE;

        break;

    case WM_MOUSEMOVE:
        hdc = GetDC(hwnd);
        if ((Drag) && (Selection)) {


            SetROP2(hdc, R2_XORPEN);
            SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));

            endX = LOWORD(lParam);
            endY = HIWORD(lParam);

            MoveToEx(hdc, x + 20, y + 20, NULL);
            LineTo(hdc, oldX, oldY);
            MoveToEx(hdc, x + 20, y + 20, NULL);
            LineTo(hdc, endX, endY);

            oldX = endX;
            oldY = endY;

            InvalidateRgn(hwnd, NULL, TRUE);
        }
        ReleaseDC(hwnd, hdc);

        break;

    case WM_TIMER:
        x = x + stepX;
        y = y + stepY;
        move++;

        if (move == 10) {
            stepX = 0;
            stepY = 0;
            move = 0;
            KillTimer(hwnd, 1);
        }
        InvalidateRgn(hwnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        KillTimer(hwnd, 1);
        break;

    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);

}