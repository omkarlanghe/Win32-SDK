class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};
class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
// {454C7AA1-C865-413A-A2A7-88F592D81A67}
const CLSID CLSID_SumSubtract = { 0x454c7aa1, 0xc865, 0x413a, 0xa2, 0xa7, 0x88, 0xf5, 0x92, 0xd8, 0x1a, 0x67 };
// {C643CC9C-FE77-4087-8CDE-105C816F5032}
const IID IID_ISum = { 0xc643cc9c, 0xfe77, 0x4087, 0x8c, 0xde, 0x10, 0x5c, 0x81, 0x6f, 0x50, 0x32 };
// {2DA59F22-471C-438E-9F84-B7A3DD18869F}
const IID IID_ISubtract = { 0x2da59f22, 0x471c, 0x438e, 0x9f, 0x84, 0xb7, 0xa3, 0xdd, 0x18, 0x86, 0x9f };

