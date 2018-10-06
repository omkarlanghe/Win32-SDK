#include<windows.h>
#include"AggregationInnerComponentWithRegFile.h"
#include"AggregationOuterComponentWithRegFile.h"

class CSumSubtract :public ISum, ISubtract
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownInner;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	CSumSubtract(void);
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

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
CSumSubtract::CSumSubtract(void)
{
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);

	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if (riid == IID_IMultiplication)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else if (riid == IID_IDivision)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
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
		return(0);
	}
	return(m_cRef);
}
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_MultiplicationDivision,
		reinterpret_cast<IUnknown *>(this),
		CLSCTX_INPROC_SERVER, IID_IUnknown, (void **)&m_pIUnknownInner);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IUnknown Interface can not be obtained from inner component"), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void **)&m_pIMultiplication);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface can not be obtained from inner component"), TEXT("Error"), MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return(E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IDivision, (void **)&m_pIDivision);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface can not be obtained from inner component"), TEXT("Error"), MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return(E_FAIL);
	}
	return(S_OK);
}
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1;
}
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}
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
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtract->InitializeInnerComponent();

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to initialize inner component"), TEXT("Error"), MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}

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
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
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
HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}
