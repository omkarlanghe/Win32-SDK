#define UNICODE
#include<windows.h>
#include "ClassFactoryDllServer.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations
IArithmetic *pISum = NULL, *pISub = NULL, *pIMul = NULL, *pIDiv = NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;

	//COM Initialization
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library can not be initialized.\n Program will now exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register window class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(AppName, TEXT("Client Of COM Dll Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//COM Uninitialization
	CoUninitialize();
	return((int)msg.wParam);
}

//window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void SafeInterfaceRelease(void);

	//variable declarations
	HRESULT hr;
	int iNum1, iNum2, iSum, iSub, iMul, iDiv;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_ArithmeticOperation, NULL, CLSCTX_INPROC_SERVER, IID_IArithmetic, (void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IArithmetic interface cannot be obtained"),TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		/*---------------------------------------------------------------------------------------------------------*/
		//ADDITION
		iNum1 = 55;
		iNum2 = 45;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d  = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		hr = pISum->QueryInterface(IID_IArithmetic, (void **)&pISub);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IArithmetic interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		pISum->Release();
		pISum = NULL;

		/*-------------------------------------------------------------------------------------------------------*/
		//SUBTRACTION
		iNum1 = 155;
		iNum2 = 145;

		pISub->SubtractionOfTwoIntegers(iNum1, iNum2, &iSub);
		wsprintf(str, TEXT("Subtract of %d and %d  = %d"), iNum1, iNum2, iSub);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		hr = pISub->QueryInterface(IID_IArithmetic, (void **)&pIMul);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IArithmetic interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		pISub->Release();
		pISub = NULL;

		/*------------------------------------------------------------------------------------------------------------*/
		//MULTIPLICATION
		iNum1 = 100;
		iNum2 = 50;

		pIMul->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMul);
		wsprintf(str, TEXT("Multiplication of %d and %d  = %d"), iNum1, iNum2, iMul);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		hr = pIMul->QueryInterface(IID_IArithmetic, (void **)&pIDiv);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IArithmetic interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		pIMul->Release();
		pIMul = NULL;

		/*--------------------------------------------------------------------------------------------------------------*/
		//DIVISION
		iNum1 = 20;
		iNum2 = 5;

		pIDiv->DivisionOfTwoIntegers(iNum1, iNum2, &iDiv);
		wsprintf(str, TEXT("Division of %d and %d  = %d"), iNum1, iNum2, iDiv);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		pIDiv->Release();
		pIDiv = NULL;

		//Destroy Window
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
	if (pISub)
	{
		pISub->Release();
		pISub = NULL;
	}
	if (pIMul)
	{
		pIMul->Release();
		pIMul = NULL;
	}
	if (pIDiv)
	{
		pIDiv->Release();
		pIDiv = NULL;
	}
}
