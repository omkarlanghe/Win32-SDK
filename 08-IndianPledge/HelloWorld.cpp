#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)

{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Windows");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Indian Pledge"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
		HDC hdc = NULL;
		PAINTSTRUCT ps;
		RECT rc;
		TCHAR str1[] = TEXT("India is my country. All Indians are my Brothers and Sisters.");
		TCHAR str2[] = TEXT("I love my country and I am proud of its rich and varied heritage.");
		TCHAR str3[] = TEXT("I shall always strive to be worthy of it.");
		TCHAR str4[] = TEXT("I shall give my parents, teachers and all elders respect and treat everyone with courtesy.");
		TCHAR str5[] = TEXT("To my country and my people, I pledge my devotion.");
		TCHAR str6[] = TEXT("In their well being and prosperity alone, lies my happiness.");
	
	switch (iMsg)

	{
	case WM_PAINT:
		GetClientRect(hwnd, &rc);

		hdc = BeginPaint(hwnd, &ps);

		SetTextColor(hdc, RGB(255, 125, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 100, 10, str1, ARRAYSIZE(str1));
		TextOut(hdc, 100, 30, str2, ARRAYSIZE(str2));
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 100, 50, str3, ARRAYSIZE(str3));
		TextOut(hdc, 100, 70, str4, ARRAYSIZE(str4));
		SetTextColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, 100, 90, str5, ARRAYSIZE(str5));
		TextOut(hdc, 100, 110, str6, ARRAYSIZE(str6));

		EndPaint(hwnd, &ps);

		break;

		case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
