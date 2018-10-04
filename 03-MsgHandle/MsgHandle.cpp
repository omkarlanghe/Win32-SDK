#include<windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Omkar"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_Create is called"), TEXT("WM_Create"), MB_OK | MB_ICONASTERISK | WMSZ_TOP);
		break;

	case WM_MOVE:
		MessageBox(hwnd, TEXT("WM_Move is called"), TEXT("WM_Move"), MB_OK | MB_ICONERROR | WMSZ_TOP);
		break;

	case WM_SIZE:
		MessageBox(hwnd, TEXT("WM_Size is called"), TEXT("WM_Size"), MB_OK | MB_ICONEXCLAMATION | WMSZ_TOP);
		break;

	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("WM_KeyDown is called"), TEXT("WM_KeyDown"), MB_OK | MB_ICONHAND | WMSZ_TOP);
		break;
	
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_LButtonDown is called"), TEXT("WM_LButtonDown"), MB_OK | MB_ICONINFORMATION | WMSZ_TOP);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
