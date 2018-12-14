#include<windows.h>
#include<stdio.h>
#include "AutomationServer.h"

// Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ComErrorDescriptionString(HWND, HRESULT);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Automation(IDispatchAutomationClient)");
	HRESULT hr;

	// code

	// COM Initialization
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library can not be initialized.\n Program will now exit."), TEXT("Error"), MB_OK);
		ComErrorDescriptionString(NULL, hr);
		exit(0);
	}

	// initialization of WNDCLASSEX
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

	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("IDispatchAutomationClient"),
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

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// COM Un-initialization
	CoUninitialize();

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// code

	IDispatch *pIDispatch = NULL;
	HRESULT hr;
	DISPID dispid;
	OLECHAR *szFunctionName1 = (OLECHAR *)L"SumOfTwoIntegers";
	OLECHAR *szFunctionName2 = (OLECHAR *)L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS param = { vArg,0,2,NULL };
	int n1, n2;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:

		// get IMyMath Interface
		hr = CoCreateInstance(CLSID_MyMath,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IDispatch,
			(void **)&pIDispatch);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("Component Can Not Be Created"), TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}

		n1 = 75;
		n2 = 25;

		// as DISPPARAMS rgvarg member receives paramenters in reverse order.
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = n2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = n1;
		param.cArgs = 2;
		param.cNamedArgs = 0;
		param.rgdispidNamedArgs = NULL;
		// reverse order of parameters
		param.rgvarg = vArg;
		// return value
		VariantInit(&vRet);

		// *** code for IMyMath->SumOfTwoIntegers() ***
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName1,
			1,
			GetUserDefaultLCID(),
			&dispid);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID For SumOfTwoIntegers()"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Invoke Function"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		wsprintf(str, TEXT("Sum Of %d And %d Is %d"), n1, n2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("SumOfTwoIntegers"), MB_OK);

		// *** code for IMyMath->SubtractionOfTwoIntegers() ***
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName2,
			1,
			GetUserDefaultLCID(),
			&dispid);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID For SubtractionOfTwoIntegers()"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		// Invoke() for IMyMath->SubtractionOfTwoIntegers
		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Invoke Function"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		wsprintf(str, TEXT("Subtraction Of %d And %d Is %d"), n1, n2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("SubtractionOfTwoIntegers"), MB_OK);

		// clean up
		VariantClear(vArg);
		VariantClear(&vRet);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR *szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		wsprintf(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		wsprintf(str, TEXT("Could not obtain error."), hr);
	}

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
