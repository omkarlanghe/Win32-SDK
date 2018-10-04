//#define UNICODE
//#include<windows.h>
class ISum : public IUnknown
{
	public:
		// ISum specific method declarations
		virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};
class ISubtract : public IUnknown
{
	public:
		//ISub specific method declarations
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};
//CLSID of SumSubtract Component
//{17654B5B-35C1-4CA1-9C23-C205207B8977}
const CLSID CLSID_SumSubtract = { 0x17654b5b, 0x35c1, 0x4ca1, 0x9c, 0x23, 0xc2, 0x5, 0x20, 0x7b, 0x89, 0x77 };
//IID of ISum Interface	
// {8D57DBBE-B070-4909-AB9A-380317AAEC83}
const IID IID_ISum = { 0x8d57dbbe, 0xb070, 0x4909, 0xab, 0x9a, 0x38, 0x3, 0x17, 0xaa, 0xec, 0x83 };
//IID of ISubtract Interface
// {8F46289A-E441-4F87-90A2-FE0CF863168F}
const IID IID_ISubtract = { 0x8f46289a, 0xe441, 0x4f87, 0x90, 0xa2, 0xfe, 0xc, 0xf8, 0x63, 0x16, 0x8f };