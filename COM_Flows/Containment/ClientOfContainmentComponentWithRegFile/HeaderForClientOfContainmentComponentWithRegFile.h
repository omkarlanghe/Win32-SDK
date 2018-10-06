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
class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};
class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};
// {454C7AA1-C865-413A-A2A7-88F592D81A67}
const CLSID CLSID_SumSubtract = { 0x454c7aa1, 0xc865, 0x413a, 0xa2, 0xa7, 0x88, 0xf5, 0x92, 0xd8, 0x1a, 0x67 };
// {C643CC9C-FE77-4087-8CDE-105C816F5032}
const IID IID_ISum = { 0xc643cc9c, 0xfe77, 0x4087, 0x8c, 0xde, 0x10, 0x5c, 0x81, 0x6f, 0x50, 0x32 };
// {2DA59F22-471C-438E-9F84-B7A3DD18869F}
const IID IID_ISubtract = { 0x2da59f22, 0x471c, 0x438e, 0x9f, 0x84, 0xb7, 0xa3, 0xdd, 0x18, 0x86, 0x9f };
// {A895F4BC-CAE7-49AF-9818-C98E9BD9ACCE}
const IID IID_IMultiplication = { 0xa895f4bc, 0xcae7, 0x49af, 0x98, 0x18, 0xc9, 0x8e, 0x9b, 0xd9, 0xac, 0xce };
// {B730C728-0B9A-41E1-AA9C-E591EF8B2749}
const IID IID_IDivision = { 0xb730c728, 0xb9a, 0x41e1, 0xaa, 0x9c, 0xe5, 0x91, 0xef, 0x8b, 0x27, 0x49 };

