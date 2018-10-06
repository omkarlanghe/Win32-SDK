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
// {D1E13BBB-8DA6-45A7-A0F2-D0DEC8A08163}
const CLSID CLSID_SumSubtract = { 0xd1e13bbb, 0x8da6, 0x45a7, 0xa0, 0xf2, 0xd0, 0xde, 0xc8, 0xa0, 0x81, 0x63 };
// {0F0134AB-C929-4DC5-BF34-E492DA137715}
const IID IID_ISum = { 0xf0134ab, 0xc929, 0x4dc5, 0xbf, 0x34, 0xe4, 0x92, 0xda, 0x13, 0x77, 0x15 };
// {80C37BAA-04EE-446D-84AB-A483D38EBE8D}
const IID IID_ISubtract = { 0x80c37baa, 0x4ee, 0x446d, 0x84, 0xab, 0xa4, 0x83, 0xd3, 0x8e, 0xbe, 0x8d };
// {0955F70C-25B2-42DC-AFAD-522EFEC287C5}
const IID IID_IMultiplication = { 0x955f70c, 0x25b2, 0x42dc, 0xaf, 0xad, 0x52, 0x2e, 0xfe, 0xc2, 0x87, 0xc5 };
// {DB5BD993-05E0-4DE7-860A-888328964D82}
const IID IID_IDivision = { 0xdb5bd993, 0x5e0, 0x4de7, 0x86, 0xa, 0x88, 0x83, 0x28, 0x96, 0x4d, 0x82 };

