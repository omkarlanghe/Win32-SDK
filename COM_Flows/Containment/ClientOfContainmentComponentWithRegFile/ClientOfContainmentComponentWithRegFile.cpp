#define UNICODE
#include<windows.h>
#include<process.h>
#include"HeaderForClientOfContainmentComponentWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR
	lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ComClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library can not be initialized.\nProgram will now exit"), TEXT("Program Error"), MB_OK);
		exit(0);
	}

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
		TEXT("Client Of COM Dll Server"),
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
	CoUninitialize();
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void SafeInterfaceRelease(void);

	HRESULT hr;
	int iNum1, iNum2, iSum, iSubtraction, iMultiplication, iDivision;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 65;
		iNum2 = 45;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str,TEXT("Sum of %d and %d = %d"),iNum1,iNum2,iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 155;
		iNum2 = 55;
		
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtraction);
		wsprintf(str,TEXT("Subtraction of %d and %d = %d"),iNum1,iNum2,iSubtraction);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void **)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISubtract->Release();
		pISubtract = NULL;

		iNum1 = 30;
		iNum2 = 25;

		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void **)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 200;
		iNum2 = 25;

		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);
		wsprintf(str, TEXT("Division Of %d and %d = %d"), iNum1, iNum2, iDivision);
		MessageBox(hwnd,str,TEXT("Result"),MB_OK);

		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}

