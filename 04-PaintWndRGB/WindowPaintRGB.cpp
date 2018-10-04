#include<windows.h>
#include "resource.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("My RepaintWindow"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int iNum = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hBrush = 0;

	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'R':
		case 'r':
			iNum = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'B':
		case 'b':
			iNum = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'G':
		case 'g':
			iNum = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'C':
		case 'c':
			iNum = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'M':
		case 'm':
			iNum = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'Y':
		case 'y':
			iNum = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'O':
		case 'o':
			iNum = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		default:
			iNum = 8;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}	
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		
		if(iNum == 1)
		{
			hBrush = CreateSolidBrush(RGB(255,0,0));
		}
		else if (iNum == 2)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (iNum == 3)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (iNum == 4)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (iNum == 5)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (iNum == 6)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (iNum == 7)
		{
			hBrush = CreateSolidBrush(RGB(255, 128, 0));
		}
		else if (iNum == 8)
		{
			hBrush = CreateSolidBrush(RGB(128, 0, 0));
		}
		SelectObject(hdc, hBrush);
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hdc);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
