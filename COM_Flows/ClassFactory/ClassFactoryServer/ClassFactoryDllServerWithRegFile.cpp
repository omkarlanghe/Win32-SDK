#define UNICODE
#include<windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//class Declaration
class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
	
public:
	//constructor method declaration
	CSumSubtract(void);
	//destructor method declaration
	~CSumSubtract(void);
	//IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//ISum specific methods declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);
	//ISubtract specific methods declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtractClassFactory(void);
	//destructor method declarations
	~CSumSubtractClassFactory(void);
	//IUnknown specific method declarations
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//IClassFactory specific method declarations
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
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

//Implementation of CSumSubtract Constructor methods
CSumSubtract::CSumSubtract(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
//Implementation of CSumSubtract's Destructor Method
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return(m_cRef);
}
//Implementation of ISum's methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}
//Implementation of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}
//Implementation od CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1;
}
//Implementation of CSumSubtractClassFactory's Destructor 
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}
//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
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
ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
//Implementation Of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	//variable declarations
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
 }

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return(hr);
}
extern "C" HRESULT __stdcall DLLCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

