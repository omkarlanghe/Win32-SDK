#include<windows.h>
#include "MyResource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR
	lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = 0;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_POPUP,
		620,
		400,
		720,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);

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

	HDC hdc1, hdc2;
	PAINTSTRUCT ps;
	RECT rc;
	static HBITMAP temp1;
	BITMAP temp2;
	HINSTANCE hInstant = NULL;

	switch (iMsg)
	{
	case WM_CREATE:

		hInstant = ((LPCREATESTRUCT)lParam)->hInstance;
		temp1 = LoadBitmap(hInstant, MAKEINTRESOURCE(MY_BITMAP));
		break;

	case WM_PAINT:
		hdc1 = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		hdc2 = CreateCompatibleDC(hdc1); //Stretchblt
		SelectObject(hdc2, temp1);
		GetObject(temp1, sizeof(BITMAP), &temp2);
		BitBlt(hdc1, 0, 0, temp2.bmWidth, temp2.bmHeight, hdc2, 0, 0, SRCCOPY);
		DeleteDC(hdc2);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'Q':
		case 'q':
			PostQuitMessage(0);
			break;
		}
		MessageBox(hwnd, TEXT("WELCOME TO WIN32 PROJECT"), TEXT(""), MB_OK);
		break;

	case WM_DESTROY:
		DeleteObject(temp1);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
