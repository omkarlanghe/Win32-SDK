#define UNICODE
#include<windows.h>
#include "ClassFactoryDllServer.h"

class CArithmetic : public IArithmetic
{
private:
	long m_cRef;
public:
	CArithmetic(void);
	~CArithmetic(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

};

class CArithmeticClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CArithmeticClassFactory(void);
	~CArithmeticClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}

/* Implementation of CArithmetic methods*/
CArithmetic::CArithmetic(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CArithmetic::~CArithmetic(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CArithmetic::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IArithmetic *>(this);
	else if (riid == IID_IArithmetic)
		*ppv = static_cast<IArithmetic *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CArithmetic::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CArithmetic::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CArithmetic::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CArithmetic::SubtractionOfTwoIntegers(int num1, int num2, int *pSub)
{
	if (num1 > num2)
	{
		*pSub = num1 - num2;
	}
	else
	{
		*pSub = num2 - num1;
	}
	return(S_OK);
}

HRESULT CArithmetic::MultiplicationOfTwoIntegers(int num1, int num2, int *pMul)
{
	*pMul = num1 * num2;
	return(S_OK);
}

HRESULT CArithmetic::DivisionOfTwoIntegers(int num1, int num2, int *pDiv)
{
	*pDiv = num1 / num2;
	return(S_OK);
}

/* Implementation of CArithmeticClassFactory's methods*/
CArithmeticClassFactory::CArithmeticClassFactory(void)
{
	m_cRef = 1;
}

CArithmeticClassFactory::~CArithmeticClassFactory(void)
{
	//no code
}

HRESULT CArithmeticClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CArithmeticClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CArithmeticClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
HRESULT CArithmeticClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CArithmetic *pCArithmetic = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	
	//create new instance of component i.e CArithmetic class
	pCArithmetic = new CArithmetic;

	if (pCArithmetic == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface
	hr = pCArithmetic->QueryInterface(riid, ppv);

	pCArithmetic->Release();
	return(hr);
}

HRESULT CArithmeticClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CArithmeticClassFactory *pCArithmeticClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_ArithmeticOperation)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCArithmeticClassFactory = new CArithmeticClassFactory;
	if (pCArithmeticClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCArithmeticClassFactory->QueryInterface(riid, ppv);
	pCArithmeticClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}
