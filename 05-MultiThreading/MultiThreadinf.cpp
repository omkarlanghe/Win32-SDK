#include<windows.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID param);
DWORD WINAPI MyThreadProcTwo(LPVOID param);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR
	lpszCmdLine, int iCmdShow)
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

	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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
	static HANDLE hThread1 = NULL, hThread2 = NULL;
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)hwnd, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread One Creating Failed"), TEXT("error!!"), MB_OK);
		}
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		if (hThread2 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread Two Creating Failed"), TEXT("error!!"), MB_OK);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is 4th Thread"), TEXT("Message"), MB_OK);
		break;

	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI MyThreadProcOne(LPVOID param)
{
	HWND hwnd;
	HDC hdc;
	TCHAR str[255];

	hwnd = (HWND)param;
	hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (int i = 0; i <= 32767; i++)
	{
		wsprintf(str, TEXT("Thread 1 -> Increasing Order Output = %d"), i);
		TextOut(hdc, 5, 5,str,(int)_tcslen(str));
	}
	ReleaseDC(hwnd, hdc);
	return 0;
}

DWORD WINAPI MyThreadProcTwo(LPVOID param)
{
	HWND hwnd;
	HDC hdc;
	TCHAR str[255];

	hwnd = (HWND)param;
	hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (int i = 32767; i >= 0; i--)
	{
		wsprintf(str, TEXT("Thread 2 -> Decreasing Order Output = %d"), i);
		TextOut(hdc, 5, 25, str, (int)_tcslen(str));
	}
	ReleaseDC(hwnd, hdc);
	return 0;
}

